#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <user_interface.h>

#include "web_assets.h"
#include "fonts.h"

namespace {

constexpr uint8_t CHANNEL_AUTO = 0;
constexpr uint8_t FALLBACK_CHANNEL = 1;
constexpr uint8_t DEFAULT_CHANNEL = CHANNEL_AUTO;
constexpr uint8_t DEFAULT_HIDDEN = 0;
constexpr uint8_t DEFAULT_MAX_CLIENTS = 4;
constexpr uint8_t MIN_CHANNEL = 1;
constexpr uint8_t MAX_CHANNEL = 13;
constexpr uint8_t MIN_CLIENTS = 1;
constexpr uint8_t MAX_CLIENTS = 4;
constexpr uint16_t DNS_PORT = 53;

const IPAddress AP_IP(192, 168, 4, 1);
const IPAddress AP_NETMASK(255, 255, 255, 0);

constexpr uint32_t CONFIG_MAGIC = 0x45535052UL;
constexpr uint16_t CONFIG_VERSION = 3;

struct Settings {
  bool configured;
  String ssid;
  String password;
  uint8_t channel;
  bool hidden;
  uint8_t maxClients;
};

struct FormValues {
  String ssid;
  uint8_t channel;
  bool hidden;
  uint8_t maxClients;
};

struct StoredConfig {
  uint32_t magic;
  uint16_t version;
  uint16_t reserved;
  uint32_t buildId;
  uint8_t configured;
  uint8_t channel;
  uint8_t hidden;
  uint8_t maxClients;
  char ssid[33];
  char password[64];
};

ESP8266WebServer server(80);
DNSServer dnsServer;
Settings settings;
uint32_t bootMillis = 0;
bool eepromReady = false;
bool captivePortalActive = false;

uint32_t firmwareBuildId() {
  const char* build = __DATE__ " " __TIME__;
  uint32_t hash = 2166136261UL;
  while (*build != '\0') {
    hash ^= static_cast<uint8_t>(*build++);
    hash *= 16777619UL;
  }
  return hash;
}

const uint32_t FIRMWARE_BUILD_ID = firmwareBuildId();

void setDefaults() {
  settings.configured = false;
  settings.ssid = "";
  settings.password = "";
  settings.channel = DEFAULT_CHANNEL;
  settings.hidden = DEFAULT_HIDDEN != 0;
  settings.maxClients = DEFAULT_MAX_CLIENTS;
}

String setupSsid() {
  char suffix[5];
  snprintf_P(suffix, sizeof(suffix), PSTR("%04X"),
             static_cast<unsigned>(ESP.getChipId() & 0xFFFF));
  String ssid = F("ESP8266-Setup-");
  ssid += suffix;
  return ssid;
}

String activeSsid() {
  return settings.configured ? settings.ssid : setupSsid();
}

const char* activePassword() {
  return settings.configured && settings.password.length() > 0
             ? settings.password.c_str()
             : nullptr;
}

bool saveSettings() {
  if (!eepromReady) {
    return false;
  }

  StoredConfig stored;
  memset(&stored, 0, sizeof(stored));
  stored.magic = CONFIG_MAGIC;
  stored.version = CONFIG_VERSION;
  stored.buildId = FIRMWARE_BUILD_ID;
  stored.configured = settings.configured ? 1 : 0;
  stored.channel = settings.channel;
  stored.hidden = settings.hidden ? 1 : 0;
  stored.maxClients = settings.maxClients;
  strncpy(stored.ssid, settings.ssid.c_str(), sizeof(stored.ssid) - 1);
  strncpy(stored.password, settings.password.c_str(), sizeof(stored.password) - 1);

  EEPROM.put(0, stored);
  const bool ok = EEPROM.commit();
  if (!ok) {
    Serial.println(F("EEPROM: commit failed."));
  }
  return ok;
}

bool clearSettings() {
  if (!eepromReady) {
    return false;
  }

  StoredConfig stored;
  memset(&stored, 0, sizeof(stored));
  EEPROM.put(0, stored);
  const bool ok = EEPROM.commit();
  if (!ok) {
    Serial.println(F("EEPROM: commit failed."));
  }
  return ok;
}

void loadSettings() {
  setDefaults();
  if (!eepromReady) {
    return;
  }

  StoredConfig stored;
  EEPROM.get(0, stored);

  if (stored.magic == CONFIG_MAGIC && stored.version == CONFIG_VERSION &&
      stored.buildId != FIRMWARE_BUILD_ID) {
    Serial.println(F("Firmware changed; clearing saved configuration."));
    clearSettings();
    setDefaults();
    return;
  }

  if (stored.magic != CONFIG_MAGIC || stored.version != CONFIG_VERSION ||
      stored.configured != 1) {
    Serial.println(F("No saved configuration; starting setup mode."));
    return;
  }

  stored.ssid[sizeof(stored.ssid) - 1] = '\0';
  stored.password[sizeof(stored.password) - 1] = '\0';

  const String storedSsid = String(stored.ssid);
  const String storedPassword = String(stored.password);
  const bool ssidValid = storedSsid.length() >= 1 && storedSsid.length() <= 31;
  const bool passwordValid =
      storedPassword.length() == 0 ||
      (storedPassword.length() >= 8 && storedPassword.length() <= 63);

  if (!ssidValid || !passwordValid) {
    Serial.println(F("Invalid configuration; starting setup mode."));
    return;
  }

  settings.configured = true;
  settings.ssid = storedSsid;
  settings.password = storedPassword;
  settings.channel = (stored.channel == CHANNEL_AUTO ||
                      (stored.channel >= MIN_CHANNEL && stored.channel <= MAX_CHANNEL))
                         ? stored.channel
                         : DEFAULT_CHANNEL;
  settings.hidden = stored.hidden != 0;
  settings.maxClients =
      (stored.maxClients >= MIN_CLIENTS && stored.maxClients <= MAX_CLIENTS)
          ? stored.maxClients
          : DEFAULT_MAX_CLIENTS;
}

FormValues formFromSettings() {
  FormValues form;
  form.ssid = settings.configured ? settings.ssid : "";
  form.channel = settings.channel;
  form.hidden = settings.hidden;
  form.maxClients = settings.maxClients;
  return form;
}

String htmlEscape(const String& input) {
  String output;
  output.reserve(input.length() + 16);
  for (size_t i = 0; i < input.length(); ++i) {
    switch (input[i]) {
      case '&': output += F("&amp;"); break;
      case '<': output += F("&lt;"); break;
      case '>': output += F("&gt;"); break;
      case '"': output += F("&quot;"); break;
      case '\'': output += F("&#39;"); break;
      default: output += input[i]; break;
    }
  }
  return output;
}

String jsonEscape(const String& input) {
  String output;
  output.reserve(input.length() + 8);
  for (size_t i = 0; i < input.length(); ++i) {
    const char c = input[i];
    if (c == '"' || c == '\\') {
      output += '\\';
      output += c;
    } else if (static_cast<uint8_t>(c) < 0x20) {
      char buffer[7];
      snprintf(buffer, sizeof(buffer), "\\u%04x",
               static_cast<unsigned>(static_cast<uint8_t>(c)));
      output += buffer;
    } else {
      output += c;
    }
  }
  return output;
}

String sanitizeInput(const String& input) {
  String output;
  output.reserve(input.length());
  for (size_t i = 0; i < input.length(); ++i) {
    const uint8_t c = static_cast<uint8_t>(input[i]);
    if (c >= 0x20 && c != 0x7F) {
      output += static_cast<char>(c);
    }
  }
  return output;
}

String macToString(const uint8_t* mac) {
  char buffer[18];
  snprintf_P(buffer, sizeof(buffer), PSTR("%02X:%02X:%02X:%02X:%02X:%02X"),
             mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(buffer);
}

String stationIpToString(const struct station_info* station) {
  IPAddress ip(station->ip.addr);
  return ip.toString();
}

String messageBox(const char* cssClass, const String& text) {
  String box = F("<div class=\"");
  box += cssClass;
  box += F("\">");
  box += text;
  box += F("</div>");
  return box;
}

String buildOptions(uint8_t from, uint8_t to, uint8_t selected) {
  String options;
  options.reserve(static_cast<size_t>(to - from + 1) * 24);
  for (uint8_t value = from; value <= to; ++value) {
    options += F("<option value=\"");
    options += value;
    options += '"';
    if (value == selected) {
      options += F(" selected");
    }
    options += '>';
    options += value;
    options += F("</option>");
  }
  return options;
}

String buildChannelOptions(uint8_t selected) {
  String options;
  options.reserve(400);
  options += F("<option value=\"0\"");
  if (selected == CHANNEL_AUTO) {
    options += F(" selected");
  }
  options += F(">Automatic</option>");
  options += buildOptions(MIN_CHANNEL, MAX_CHANNEL, selected);
  return options;
}

String renderConfigPage(const FormValues& form, const String& notice,
                        const String& error) {
  String page = FPSTR(CONFIG_HTML);

  String setupNotice;
  if (!settings.configured) {
    String text = F("Initial setup: The access point <strong>");
    text += htmlEscape(setupSsid());
    text += F("</strong> is open. Please set a network name and password.");
    setupNotice = messageBox("notice", text);
  }

  page.replace("%SETUPNOTICE%", setupNotice);
  page.replace("%NOTICE%", notice);
  page.replace("%ERROR%", error);
  page.replace("%CHANNEL_OPTIONS%", buildChannelOptions(form.channel));
  page.replace("%CLIENTS_OPTIONS%", buildOptions(MIN_CLIENTS, MAX_CLIENTS, form.maxClients));
  page.replace("%HIDDEN_CHECKED%", form.hidden ? "checked" : "");
  page.replace("%PASSSTATE%",
               !settings.configured
                   ? "not configured yet"
                   : (settings.password.length() > 0 ? "set" : "open"));
  page.replace("%BACKLINK%",
               settings.configured
                   ? "<a class=\"btn btn-secondary\" href=\"/\">View Status</a>"
                   : "");
  page.replace("%SSID%", htmlEscape(form.ssid));
  return page;
}

void sendProgmem(const char* data, const char* contentType) {
  server.sendHeader("Cache-Control", "no-store, max-age=0");
  server.send_P(200, contentType, data);
}

void sendFont(const uint8_t* data, size_t length) {
  server.sendHeader("Cache-Control", "public, max-age=31536000, immutable");
  server.send_P(200, PSTR("font/woff2"), reinterpret_cast<PGM_P>(data), length);
}

void sendActionPage(const String& message) {
  String page = FPSTR(ACTION_HTML);
  page.replace("%MESSAGE%", message);
  server.sendHeader("Cache-Control", "no-store, max-age=0");
  server.send(200, "text/html; charset=utf-8", page);
}

void handleRoot() {
  if (!settings.configured) {
    server.sendHeader("Location", "/config", true);
    server.sendHeader("Cache-Control", "no-store, max-age=0");
    server.send(302, "text/plain; charset=utf-8", F("Setup required"));
    return;
  }
  sendProgmem(INDEX_HTML, "text/html; charset=utf-8");
}

void handleCss() {
  sendProgmem(WEB_CSS, "text/css; charset=utf-8");
}

void handleJs() {
  sendProgmem(APP_JS, "application/javascript; charset=utf-8");
}

void handleShareTechMono400() {
  sendFont(FONT_SHARE_TECH_MONO_400, FONT_SHARE_TECH_MONO_400_LEN);
}

void handleConfig() {
  const String page = renderConfigPage(formFromSettings(), "", "");
  server.sendHeader("Cache-Control", "no-store, max-age=0");
  server.send(200, "text/html; charset=utf-8", page);
}

String buildStatusJson() {
  String json;
  json.reserve(1152);

  char chipId[16];
  snprintf_P(chipId, sizeof(chipId), PSTR("%08X"), ESP.getChipId());

  json += F("{\"uptime\":");
  json += (millis() - bootMillis) / 1000UL;
  json += F(",\"freeHeap\":");
  json += ESP.getFreeHeap();
  json += F(",\"clients\":");
  json += WiFi.softAPgetStationNum();
  json += F(",\"maxClients\":");
  json += settings.maxClients;
  json += F(",\"configured\":");
  json += settings.configured ? F("true") : F("false");
  json += F(",\"ssid\":\"");
  json += jsonEscape(activeSsid());
  json += F("\",\"ip\":\"");
  json += WiFi.softAPIP().toString();
  json += F("\",\"mac\":\"");
  json += WiFi.softAPmacAddress();
  json += F("\",\"channel\":");
  json += WiFi.channel();
  json += F(",\"hidden\":");
  json += settings.hidden ? F("true") : F("false");
  json += F(",\"security\":\"");
  if (settings.configured && settings.password.length() > 0) {
    json += F("WPA2-PSK");
  } else {
    json += F("OPEN");
  }
  json += F("\",\"chipId\":\"");
  json += chipId;
  json += F("\",\"cpuMhz\":");
  json += ESP.getCpuFreqMHz();
  json += F(",\"flashKb\":");
  json += ESP.getFlashChipRealSize() / 1024UL;
  json += F(",\"sdk\":\"");
  json += jsonEscape(String(ESP.getSdkVersion()));
  json += F("\",\"core\":\"");
  json += jsonEscape(ESP.getCoreVersion());
  json += F("\",\"reset\":\"");
  json += jsonEscape(ESP.getResetReason());
  json += F("\",\"stationList\":[");

  struct station_info* stations = wifi_softap_get_station_info();
  bool first = true;
  for (struct station_info* station = stations; station != nullptr;
       station = STAILQ_NEXT(station, next)) {
    if (!first) {
      json += ',';
    }
    first = false;
    json += F("{\"mac\":\"");
    json += macToString(station->bssid);
    json += F("\",\"ip\":\"");
    json += stationIpToString(station);
    json += F("\"}");
  }
  wifi_softap_free_station_info();

  json += F("]}");
  return json;
}

void handleStatus() {
  server.sendHeader("Cache-Control", "no-store, max-age=0");
  server.send(200, "application/json; charset=utf-8", buildStatusJson());
}

void handleSave() {
  const String ssid = sanitizeInput(server.arg("ssid"));
  const String password = sanitizeInput(server.arg("pass"));
  const int channelValue = server.arg("channel").toInt();
  const int maxClientsValue = server.arg("maxClients").toInt();
  const bool hidden = server.hasArg("hidden");

  String error;
  if (ssid.length() == 0) {
    error = F("Network name must not be empty.");
  } else if (ssid.length() > 31) {
    error = F("Network name must be at most 31 characters.");
  } else if (password.length() > 0 && password.length() < 8) {
    error = F("Password must be at least 8 characters (or empty for an open network).");
  } else if (password.length() > 63) {
    error = F("Password must be at most 63 characters.");
  } else if (channelValue < CHANNEL_AUTO || channelValue > MAX_CHANNEL) {
    error = F("Channel must be Automatic or between 1 and 13.");
  } else if (maxClientsValue < MIN_CLIENTS || maxClientsValue > MAX_CLIENTS) {
    error = F("Maximum clients must be between 1 and 4.");
  }

  FormValues form;
  form.ssid = ssid;
  form.channel = (channelValue == CHANNEL_AUTO ||
                  (channelValue >= MIN_CHANNEL && channelValue <= MAX_CHANNEL))
                     ? static_cast<uint8_t>(channelValue)
                     : DEFAULT_CHANNEL;
  form.hidden = hidden;
  form.maxClients =
      (maxClientsValue >= MIN_CLIENTS && maxClientsValue <= MAX_CLIENTS)
          ? static_cast<uint8_t>(maxClientsValue)
          : DEFAULT_MAX_CLIENTS;

  if (error.length() > 0) {
    const String page = renderConfigPage(form, "", messageBox("error", error));
    server.sendHeader("Cache-Control", "no-store, max-age=0");
    server.send(200, "text/html; charset=utf-8", page);
    return;
  }

  const bool previousConfigured = settings.configured;
  const String previousSsid = settings.ssid;
  const String previousPassword = settings.password;
  const uint8_t previousChannel = settings.channel;
  const bool previousHidden = settings.hidden;
  const uint8_t previousMaxClients = settings.maxClients;

  settings.configured = true;
  settings.ssid = ssid;
  settings.password = password;
  settings.channel = form.channel;
  settings.hidden = hidden;
  settings.maxClients = form.maxClients;

  if (!saveSettings()) {
    settings.configured = previousConfigured;
    settings.ssid = previousSsid;
    settings.password = previousPassword;
    settings.channel = previousChannel;
    settings.hidden = previousHidden;
    settings.maxClients = previousMaxClients;

    const String page = renderConfigPage(
        form, "", messageBox("error", F("Could not save the configuration to EEPROM.")));
    server.sendHeader("Cache-Control", "no-store, max-age=0");
    server.send(200, "text/html; charset=utf-8", page);
    return;
  }

  if (!previousConfigured) {
    String message = F("Setup is complete. The ESP8266 will now restart with the network <strong>");
    message += htmlEscape(ssid);
    message += F("</strong>.");
    sendActionPage(message);
  } else {
    sendActionPage(F("Settings saved. The ESP8266 will restart now."));
  }

  dnsServer.stop();
  captivePortalActive = false;
  server.client().flush();
  delay(1200);
  ESP.restart();
}

void handleReboot() {
  sendActionPage(F("The ESP8266 is restarting."));
  server.client().flush();
  delay(800);
  ESP.restart();
}

uint8_t chooseBestChannel() {
  Serial.println(F("Scanning Wi-Fi channels ..."));

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  const int networkCount = WiFi.scanNetworks(false, true);
  uint8_t bestChannel = FALLBACK_CHANNEL;
  int bestScore = 1000000;

  if (networkCount > 0) {
    const uint8_t candidates[] = {1, 6, 11};
    for (uint8_t candidate : candidates) {
      int score = 0;
      for (int i = 0; i < networkCount; ++i) {
        const int channel = WiFi.channel(i);
        if (channel < MIN_CHANNEL || channel > MAX_CHANNEL) {
          continue;
        }
        const int distance = channel > candidate ? channel - candidate : candidate - channel;
        if (distance > 4) {
          continue;
        }
        const int rssi = WiFi.RSSI(i);
        const int strength = rssi >= -60 ? 3 : (rssi >= -75 ? 2 : 1);
        score += (5 - distance) * strength;
      }
      if (score < bestScore) {
        bestScore = score;
        bestChannel = candidate;
      }
    }
  }

  WiFi.scanDelete();
  Serial.print(F("Auto channel: "));
  Serial.println(bestChannel);
  return bestChannel;
}

void handleFactoryReset() {
  if (!clearSettings()) {
    sendActionPage(F("Could not clear the settings. The previous configuration remains active."));
    return;
  }

  setDefaults();
  sendActionPage(F("Factory reset complete. The ESP8266 will restart in open setup mode."));
  server.client().flush();
  delay(1200);
  ESP.restart();
}

void handleCaptivePortal() {
  server.sendHeader("Cache-Control", "no-store, max-age=0");

  if (settings.configured) {
    const String uri = server.uri();
    if (uri == F("/connecttest.txt")) {
      server.send(200, "text/plain; charset=utf-8", F("Microsoft Connect Test"));
    } else if (uri == F("/ncsi.txt")) {
      server.send(200, "text/plain; charset=utf-8", F("Microsoft NCSI"));
    } else if (uri == F("/generate_204") || uri == F("/gen_204") ||
               uri == F("/redirect") || uri == F("/fwlink")) {
      server.send(204, "text/plain", "");
    } else {
      server.send(200, "text/html; charset=utf-8", F("Success"));
    }
    return;
  }

  const String target = String(F("http://")) + WiFi.softAPIP().toString() + F("/config");
  server.sendHeader("Location", target, true);
  server.send(302, "text/plain; charset=utf-8", F("Redirecting to setup"));
}

void handleFavicon() {
  server.send(204, "text/plain", "");
}

void handleNotFound() {
  if (server.uri().startsWith(F("/api/"))) {
    server.send(404, "application/json; charset=utf-8", F("{\"error\":\"not found\"}"));
    return;
  }
  if (server.method() == HTTP_OPTIONS) {
    server.send(204, "text/plain", "");
    return;
  }
  if (!captivePortalActive) {
    server.send(404, "text/plain; charset=utf-8", F("Not found"));
    return;
  }
  handleCaptivePortal();
}

void registerRoutes() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/index.html", HTTP_GET, handleRoot);
  server.on("/style.css", HTTP_GET, handleCss);
  server.on("/app.js", HTTP_GET, handleJs);
  server.on("/fonts/share-tech-mono-400.woff2", HTTP_GET, handleShareTechMono400);
  server.on("/config", HTTP_GET, handleConfig);
  server.on("/save", HTTP_POST, handleSave);
  server.on("/reboot", HTTP_POST, handleReboot);
  server.on("/factory", HTTP_POST, handleFactoryReset);
  server.on("/api/status", HTTP_GET, handleStatus);
  server.on("/favicon.ico", HTTP_GET, handleFavicon);

  server.on("/generate_204", HTTP_GET, handleCaptivePortal);
  server.on("/gen_204", HTTP_GET, handleCaptivePortal);
  server.on("/hotspot-detect.html", HTTP_GET, handleCaptivePortal);
  server.on("/library/test/success.html", HTTP_GET, handleCaptivePortal);
  server.on("/connecttest.txt", HTTP_GET, handleCaptivePortal);
  server.on("/redirect", HTTP_GET, handleCaptivePortal);
  server.on("/ncsi.txt", HTTP_GET, handleCaptivePortal);
  server.on("/fwlink", HTTP_GET, handleCaptivePortal);

  server.onNotFound(handleNotFound);
}

}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();
  Serial.println(F("================================"));
  Serial.println(F(" ESPRouter - ESP8266 Access Point"));
  Serial.println(F("================================"));

  bootMillis = millis();

  EEPROM.begin(sizeof(StoredConfig));
  eepromReady = true;
  loadSettings();

  WiFi.persistent(false);

  uint8_t apChannel = settings.channel;
  if (apChannel == CHANNEL_AUTO) {
    apChannel = chooseBestChannel();
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_IP, AP_NETMASK);

  String apSsid = activeSsid();
  const char* apPassword = activePassword();
  bool apOk = WiFi.softAP(apSsid.c_str(), apPassword, apChannel,
                          settings.hidden ? 1 : 0, settings.maxClients);

  if (!apOk && apPassword != nullptr) {
    Serial.println(F("SoftAP with saved settings failed; starting setup mode ..."));
    WiFi.softAPdisconnect(true);
    setDefaults();
    apSsid = activeSsid();
    apOk = WiFi.softAP(apSsid.c_str(), nullptr, apChannel, 0, settings.maxClients);
  }

  delay(300);

  Serial.print(F("Mode:      "));
  Serial.println(settings.configured ? F("configured") : F("initial setup (open)"));
  Serial.print(F("SSID:      "));
  Serial.println(apSsid);
  Serial.print(F("Password:  "));
  if (settings.configured && settings.password.length() > 0) {
    Serial.println(F("(set)"));
  } else {
    Serial.println(F("(open)"));
  }
  Serial.print(F("IP:        "));
  Serial.println(WiFi.softAPIP());
  Serial.print(F("MAC:       "));
  Serial.println(WiFi.softAPmacAddress());
  Serial.print(F("Channel:   "));
  Serial.println(WiFi.channel());
  if (!apOk) {
    Serial.println(F("WARNING: Could not start the SoftAP."));
  }

  captivePortalActive = !settings.configured;
  if (captivePortalActive) {
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
  }

  registerRoutes();
  server.begin();

  Serial.println(F("HTTP:      http://192.168.4.1"));
  if (!settings.configured) {
    Serial.println(F("Connect to the open Wi-Fi network and visit http://192.168.4.1"));
  }
  Serial.println(F("Ready."));
}

void loop() {
  if (captivePortalActive) {
    dnsServer.processNextRequest();
  }
  server.handleClient();
}
