# ESPRouter

ESPRouter is a small ESP8266 firmware that provides a standalone Wi-Fi access point with DHCP and a local web interface. It does **not** require or share an Internet connection.

On first boot, the ESP8266 opens an open setup Wi-Fi network. After setup, it starts with the chosen network name and password. Settings can be changed at any time at `http://192.168.4.1` while connected to the access point.

## Features

- Open setup access point `ESP8266-Setup-XXXX` on first boot
- Captive portal only during first setup; normal operation has no forced portal
- Configurable SSID, password, Wi-Fi channel, hidden network, and maximum client count
- Automatic channel selection or manual channel 1 to 13
- Status page with uptime, free heap, clients, SSID, IP, MAC, channel, security, and device information
- List of currently connected devices
- Settings persist in EEPROM across normal restarts and power cycles
- English interface with a permanent light theme
- Embedded Share Tech Mono font (SIL OFL 1.1)
- A new firmware build clears saved settings
- No external libraries

## First Setup

1. Flash the firmware and restart the ESP8266.
2. Connect to the open Wi-Fi network `ESP8266-Setup-XXXX`. `XXXX` is the low 16-bit chip ID in hex.
3. Open `http://192.168.4.1` in a browser. During first setup, many devices open the page automatically through the captive portal.
4. Set the network name, password, channel, maximum clients, and optionally **Hide Wi-Fi network**.
5. Select **Save & Restart**.
6. Connect to the newly configured Wi-Fi network and open `http://192.168.4.1` again.

The setup Wi-Fi network stays open until a configuration has been saved. After setup, the captive portal and wildcard DNS are disabled; devices only show it again after a factory reset.

## Defaults

| Setting | Value |
| --- | --- |
| Setup SSID | `ESP8266-Setup-XXXX` |
| Setup password | open |
| Address | `http://192.168.4.1` |
| Network | `192.168.4.0/24` |
| Wi-Fi channel | `Automatic` |
| Maximum clients | `4` |
| Hidden network | off |

There is no default password for the access point.

## Configuration

- **SSID:** 1 to 31 characters.
- **Password:** leave empty for an open network, otherwise 8 to 63 characters. Saving an empty field removes an existing password.
- **Channel:** **Automatic** scans at boot and picks the least busy of channels 1, 6 and 11. Manual selection allows 1 to 13; channels 1, 6 and 11 usually overlap the least.
- **Maximum clients:** 1 to 4 simultaneous devices.
- **Hide network:** the SSID is not actively broadcast and must be added manually on the client.
- After saving, the ESP8266 restarts automatically.
- Normal restarts keep the settings. Flashing a new firmware build clears them once; reflashing the exact same binary cannot be detected.
- **Factory Reset** deletes all settings and restarts in open setup mode.

## Hardware

The default board is `nodemcuv2` (NodeMCU 1.0 / ESP-12E, 4 MB flash). For other boards, change the board ID in `platformio.ini`, for example:

- `d1_mini` – Wemos D1 mini
- `esp12e` – ESP-12E
- `esp01_1m` – ESP-01 with 1 MB flash

The ESP8266 only operates on **2.4 GHz**.

## Build and Flash

Install PlatformIO Core once:

```powershell
python -m pip install --user platformio
```

In the project directory:

```powershell
pio run
pio run -t upload
pio device monitor
```

If `pio` is not on PATH after installation:

```powershell
python -m platformio run
python -m platformio run -t upload
python -m platformio device monitor
```

Alternatively, open the PlatformIO extension in VS Code and load the project.

The finished firmware is written to `.pio/build/nodemcuv2/firmware.bin`.

Tested with PlatformIO 6.2.0, platform `espressif8266` 4.2.1, and Arduino Core 3.1.2.

## Credits

- Share Tech Mono by Ray Larabie / Typodermic Fonts, licensed under SIL OFL 1.1.
- Font files distributed via [Fontsource](https://fontsource.org).

## License

MIT – see [LICENSE](LICENSE). The embedded font is licensed under the SIL Open Font License 1.1, see [LICENSES/FONTS.txt](LICENSES/FONTS.txt).
