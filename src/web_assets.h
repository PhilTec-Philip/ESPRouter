#pragma once

#include <pgmspace.h>

static const char WEB_CSS[] PROGMEM = R"=====(
@font-face {
  font-family: 'Share Tech Mono';
  font-style: normal;
  font-weight: 400;
  font-display: swap;
  src: url('/fonts/share-tech-mono-400.woff2') format('woff2');
}

:root {
  --font-display: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  --font-mono: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  color-scheme: light;
  --bg-body: #ffffff;
  --bg-card: #ffffff;
  --bg-section-alt: #f8f9fa;
  --text-primary: #111111;
  --text-heading: #000000;
  --text-subheading: #222222;
  --text-muted: #666666;
  --border: #111111;
  --accent: #007a8f;
  --accent-hover: #005b6b;
  --accent-glow: rgba(0, 122, 143, 0.1);
  --plate-bg: #ffffff;
  --plate-text: #000000;
  --plate-text-dim: #444444;
  --footer-bg: #ffffff;
  --footer-text: #111111;
  --footer-text-muted: #666666;
  --lcd-bg: #cbd5e1;
  --lcd-border: #111111;
  --lcd-text: #000000;
  --lcd-dim: #444444;
  --lcd-grid: rgba(0, 122, 143, 0.25);
  --shadow-sm: rgba(0, 0, 0, 0.15);
  --shadow-md: rgba(0, 0, 0, 0.25);
  --danger: #b3261e;
  --danger-bg: rgba(179, 38, 30, 0.08);
}

*,
*::before,
*::after {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  border-radius: 0;
}

html {
  background: var(--footer-bg);
  scroll-behavior: smooth;
}

body {
  font-family: var(--font-mono);
  background: var(--bg-body);
  color: var(--text-primary);
  line-height: 1.7;
  min-height: 100vh;
  display: flex;
  flex-direction: column;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

::-webkit-scrollbar {
  width: 8px;
  height: 8px;
}

::-webkit-scrollbar-track {
  background: transparent;
}

::-webkit-scrollbar-thumb {
  background: var(--border);
}

::-webkit-scrollbar-thumb:hover {
  background: var(--accent);
}

a:focus-visible,
button:focus-visible,
input:focus-visible,
select:focus-visible,
label:has(input:focus-visible) {
  outline: 2px dashed var(--accent);
  outline-offset: 2px;
}

::selection {
  background: var(--accent);
  color: #0c0f11;
}

header {
  position: sticky;
  top: 0;
  z-index: 999;
  background: var(--plate-bg);
  border-bottom: 1px solid var(--border);
  padding: 0.75rem 2rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  flex-wrap: wrap;
  gap: 1rem;
}

.scroll-progress {
  position: absolute;
  bottom: -1px;
  left: 0;
  width: 0;
  height: 3px;
  background: var(--accent);
  z-index: 1;
  pointer-events: none;
  transition: width 0.05s linear;
}

.header-left {
  display: flex;
  align-items: center;
  min-width: 0;
}

.brand-line {
  display: flex;
  align-items: center;
  gap: 0.6rem;
  flex-wrap: wrap;
}

.header-left h1 {
  font-family: var(--font-display);
  font-size: 1.35rem;
  color: var(--plate-text);
  font-weight: 400;
  letter-spacing: 2px;
  text-transform: uppercase;
  line-height: 1.1;
}

.brand-eyebrow {
  margin-top: 0.18rem;
  color: var(--plate-text-dim);
  font-family: var(--font-display);
  font-size: 0.68rem;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.brand-eyebrow span {
  color: var(--accent);
}

.version-tag {
  display: inline-block;
  padding: 0.12rem 0.45rem;
  border: 1px solid var(--accent);
  color: var(--accent);
  font-family: var(--font-display);
  font-size: 0.68rem;
  line-height: 1.4;
  letter-spacing: 2px;
  white-space: nowrap;
}

nav {
  display: flex;
  gap: 0.25rem;
  flex-wrap: wrap;
  align-items: center;
}

nav a {
  color: var(--plate-text-dim);
  text-decoration: none;
  padding: 0.45rem 0.9rem;
  font-family: var(--font-mono);
  font-size: 0.82rem;
  font-weight: 500;
  text-transform: uppercase;
  letter-spacing: 0.5px;
  box-shadow: inset 0 -2px 0 transparent;
  transition: color 0.08s linear, box-shadow 0.08s linear, background 0.08s linear;
  white-space: nowrap;
}

nav a:hover {
  background: rgba(127, 127, 127, 0.1);
  color: var(--plate-text);
}

nav a.active {
  background: rgba(127, 127, 127, 0.12);
  color: var(--plate-text);
  font-weight: 700;
  box-shadow: inset 0 -2px 0 var(--accent);
}

main {
  flex: 1;
  max-width: 1120px;
  width: 100%;
  margin: 2.5rem auto 0;
  padding: 0 2rem 2.5rem;
  background: var(--bg-body);
}

.hero {
  text-align: center;
  padding: 3rem 2rem;
  background: var(--plate-bg);
  margin-bottom: 2rem;
  border: 1px solid var(--border);
  box-shadow: 4px 4px 0 var(--shadow-sm);
  position: relative;
  overflow: hidden;
}

.hero-small {
  padding: 2rem;
}

.hero-eyebrow,
.section-eyebrow {
  color: var(--text-muted);
  font-family: var(--font-display);
  font-size: 0.72rem;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.hero-eyebrow {
  color: var(--accent);
  margin-bottom: 0.75rem;
}

.section-eyebrow {
  margin: -0.2rem 0 0.15rem;
}

.section-eyebrow span {
  color: var(--accent);
}

.hero h2 {
  color: var(--text-primary);
  font-family: var(--font-display);
  font-size: 1.5rem;
  border: none;
  margin-bottom: 0.5rem;
  font-weight: 400;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.hero .call {
  display: inline-block;
  margin: 1.5rem 0 0.75rem;
  padding: 0.5rem 2.5rem;
  background: transparent;
  color: var(--accent);
  font-family: var(--font-display);
  font-size: 1.8rem;
  font-weight: 400;
  border: 1px solid var(--border);
  letter-spacing: 6px;
}

.hero .call::after {
  content: '_';
  margin-left: 4px;
  animation: blinkCursor 1.1s steps(1) infinite;
}

@keyframes blinkCursor {
  0%, 49% { opacity: 1; }
  50%, 100% { opacity: 0; }
}

.hero .subtitle {
  color: var(--plate-text-dim);
  font-size: 1.05rem;
  font-weight: 400;
  letter-spacing: 1px;
  margin-top: 0.5rem;
}

section {
  position: relative;
  background: var(--bg-card);
  padding: 2rem;
  margin-bottom: 1.5rem;
  border: 1px solid var(--border);
  box-shadow: 4px 4px 0 var(--shadow-sm);
}

section:hover {
  box-shadow: 5px 5px 0 var(--shadow-md);
}

section h2 {
  color: var(--text-heading);
  font-family: var(--font-display);
  font-size: 1.3rem;
  margin-bottom: 1rem;
  padding-bottom: 0.6rem;
  border-bottom: 1px solid var(--border);
  font-weight: 400;
  letter-spacing: 1px;
  text-transform: uppercase;
}

section h2::before {
  content: '[ ';
  color: var(--accent);
}

section h2::after {
  content: ' ]';
  color: var(--accent);
}

section h3 {
  color: var(--text-subheading);
  font-family: var(--font-display);
  font-size: 1.02rem;
  margin: 1.5rem 0 0.75rem;
  font-weight: 400;
  letter-spacing: 0.5px;
}

section h3::before {
  content: '// ';
  color: var(--accent);
}

p {
  margin-bottom: 0.75rem;
}

a {
  color: var(--accent);
  text-decoration: none;
  border-bottom: 1px dashed transparent;
  transition: color 0.08s linear, border-color 0.08s linear;
}

a:hover {
  color: var(--accent-hover);
  border-bottom-color: currentColor;
}

.grid-2 {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1.5rem;
}

.grid-2 > section {
  margin-bottom: 0;
}

.btn {
  display: inline-block;
  padding: 0.65rem 1.5rem;
  background: var(--accent);
  color: #0c0f11;
  border: 1px solid var(--accent);
  font-family: var(--font-mono);
  font-size: 0.82rem;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 1px;
  text-decoration: none;
  box-shadow: 3px 3px 0 var(--shadow-sm);
  cursor: pointer;
  transition: background 0.08s linear, color 0.08s linear, box-shadow 0.08s linear, border-color 0.08s linear;
}

.btn:hover {
  background: transparent;
  color: var(--accent);
  border-color: var(--accent);
  box-shadow: 4px 4px 0 var(--shadow-md);
}

.btn:active {
  transform: translate(2px, 2px);
  box-shadow: none;
}

.btn-secondary {
  background: transparent;
  color: var(--text-primary);
  border-color: var(--border);
}

.btn-secondary:hover {
  color: var(--accent);
  border-color: var(--accent);
}

.btn-danger {
  background: transparent;
  color: var(--danger);
  border-color: var(--danger);
}

.btn-danger:hover {
  background: var(--danger);
  color: #ffffff;
  border-color: var(--danger);
}

.time-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(170px, 1fr));
  gap: 0;
  margin-top: 1rem;
  background: var(--lcd-bg);
  border: 1px solid var(--lcd-border);
  box-shadow:
    inset 0 0 0 1px #000,
    inset 0 0 28px rgba(0, 0, 0, 0.65),
    4px 4px 0 var(--shadow-sm);
  position: relative;
  overflow: hidden;
}

.time-grid::after {
  content: '';
  position: absolute;
  inset: 0;
  z-index: 2;
  pointer-events: none;
  background: repeating-linear-gradient(0deg, rgba(0, 0, 0, 0.22) 0 1px, transparent 1px 3px);
}

.time-card {
  background: transparent;
  border: none;
  border-right: 1px dashed var(--lcd-grid);
  padding: 1.1rem 1rem 1.25rem;
  text-align: center;
  position: relative;
  z-index: 1;
}

.time-card:last-child {
  border-right: none;
}

.time-card .time-label {
  display: block;
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 3px;
  color: var(--lcd-dim);
  margin-bottom: 0.4rem;
}

.time-card .time-value {
  display: block;
  font-family: var(--font-display);
  font-size: 1.7rem;
  font-weight: 400;
  color: var(--lcd-text);
  text-shadow:
    0 0 6px var(--accent-glow),
    0 0 18px var(--accent-glow);
  font-variant-numeric: tabular-nums;
  letter-spacing: 2px;
}

.time-card .time-value::after {
  content: '_';
  margin-left: 2px;
  animation: blinkCursor 1s steps(1) infinite;
}

.time-card .time-zone {
  display: block;
  font-size: 0.68rem;
  color: var(--lcd-dim);
  letter-spacing: 1px;
  margin-top: 0.3rem;
}

.time-hint {
  margin-top: 1rem;
  font-size: 0.78rem;
  color: var(--text-muted);
}

.time-hint::before {
  content: '// ';
  color: var(--accent);
}

.table-wrap {
  overflow-x: auto;
  -webkit-overflow-scrolling: touch;
}

.data-table {
  width: 100%;
  border-collapse: collapse;
  margin: 0.5rem 0 1.25rem;
  font-size: 0.85rem;
  border: 1px solid var(--border);
}

.data-table th {
  background: var(--plate-bg);
  color: var(--plate-text-dim);
  padding: 0.5rem 0.75rem;
  text-align: left;
  font-family: var(--font-mono);
  font-weight: 700;
  font-size: 0.75rem;
  text-transform: uppercase;
  letter-spacing: 1px;
  border-bottom: 1px solid var(--border);
}

.data-table td {
  padding: 0.4rem 0.75rem;
  border-bottom: 1px solid var(--border);
  word-break: break-word;
}

.data-table tr:last-child td {
  border-bottom: none;
}

.data-table tr:nth-child(even) td {
  background: var(--bg-section-alt);
}

.data-table th:first-child {
  width: 36%;
}

.hint,
.muted {
  font-size: 0.78rem;
  color: var(--text-muted);
}

.field {
  margin-bottom: 1.25rem;
}

.field label {
  display: block;
  font-family: var(--font-display);
  font-size: 0.85rem;
  letter-spacing: 1px;
  text-transform: uppercase;
  margin-bottom: 0.4rem;
  color: var(--text-subheading);
}

.field label::before {
  content: '// ';
  color: var(--accent);
}

.field input,
.field select {
  width: 100%;
  max-width: 520px;
  padding: 0.7rem 0.85rem;
  background: var(--plate-bg);
  border: 1px solid var(--border);
  color: var(--text-primary);
  font-family: var(--font-mono);
  font-size: 1rem;
  outline: none;
  transition: border-color 0.08s linear, box-shadow 0.08s linear;
}

.field select {
  cursor: pointer;
}

.field input:focus,
.field select:focus {
  border-color: var(--accent);
  box-shadow: 3px 3px 0 var(--accent-glow);
}

.field input::placeholder {
  color: var(--text-muted);
}

.field-grid {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 1rem;
}

.checkbox-field {
  display: flex;
  align-items: flex-start;
  gap: 0.8rem;
  margin-bottom: 1.25rem;
  padding: 0.8rem 0.9rem;
  border: 1px solid var(--border);
  background: var(--bg-section-alt);
  cursor: pointer;
  transition: border-color 0.08s linear, background 0.08s linear, box-shadow 0.08s linear;
}

.checkbox-field:hover {
  border-color: var(--accent);
  background: var(--bg-card);
  box-shadow: 3px 3px 0 var(--shadow-sm);
}

.checkbox-field input[type="checkbox"] {
  width: 1.05rem;
  height: 1.05rem;
  margin-top: 0.25rem;
  accent-color: var(--accent);
  flex-shrink: 0;
  cursor: pointer;
}

.checkbox-field input[type="checkbox"]:focus-visible {
  outline: 2px dashed var(--accent);
  outline-offset: 2px;
}

.checkbox-field .checkbox-title {
  display: block;
  font-family: var(--font-display);
  font-size: 0.85rem;
  letter-spacing: 1px;
  text-transform: uppercase;
  color: var(--text-subheading);
}

.checkbox-field .checkbox-title::before {
  content: '// ';
  color: var(--accent);
}

.checkbox-field .hint {
  display: block;
  margin-top: 0.25rem;
}

.form-actions {
  display: flex;
  gap: 1rem;
  flex-wrap: wrap;
  align-items: center;
  margin-top: 0.5rem;
}

.notice,
.error {
  padding: 0.85rem 1rem;
  margin-bottom: 1.25rem;
  border: 1px solid var(--accent);
  background: var(--accent-glow);
  color: var(--text-primary);
  font-size: 0.85rem;
}

.notice::before {
  content: '// ';
  color: var(--accent);
}

.error {
  border-color: var(--danger);
  background: var(--danger-bg);
  color: var(--danger);
}

.error::before {
  content: '!! ';
}

.danger-zone {
  border-color: var(--danger);
}

.danger-zone h2 {
  color: var(--danger);
  border-bottom-color: var(--danger);
}

.danger-zone h2::before,
.danger-zone h2::after {
  color: var(--danger);
}

footer {
  background: var(--footer-bg);
  border-top: 1px solid var(--border);
  text-align: center;
  padding: 1.25rem;
  font-size: 0.82rem;
  color: var(--footer-text-muted);
  letter-spacing: 0.3px;
}

footer p {
  margin: 0.3rem 0;
}

footer a {
  color: var(--footer-text);
  border-bottom-color: transparent;
}

footer a:hover {
  color: var(--accent);
}

.footer-muted {
  font-size: 0.75rem;
}

@media (max-width: 768px) {
  header {
    padding: 0.75rem 1rem;
    gap: 0.75rem;
  }

  main {
    padding: 0 1rem 2rem;
    margin-top: 1.5rem;
  }

  section {
    padding: 1.25rem;
  }

  .hero {
    padding: 2rem 1rem;
  }

  .hero .call {
    font-size: 1.4rem;
    letter-spacing: 3px;
    padding: 0.45rem 1.4rem;
  }

  .grid-2,
  .field-grid {
    grid-template-columns: 1fr;
  }

  .grid-2 > section {
    margin-bottom: 1.5rem;
  }

  .field-grid {
    gap: 0;
  }

  .time-card {
    border-right: none;
    border-bottom: 1px dashed var(--lcd-grid);
  }

  .time-card:last-child {
    border-bottom: none;
  }

  .header-left h1 {
    font-size: 1.05rem;
  }

  .brand-eyebrow {
    font-size: 0.6rem;
    letter-spacing: 1px;
  }

  nav {
    order: 3;
    width: 100%;
    border-top: 1px solid var(--border);
    padding-top: 0.35rem;
  }

  nav a {
    flex: 1;
    padding: 0.35rem 0.55rem;
    font-size: 0.75rem;
    text-align: center;
  }

  .data-table th:first-child {
    width: 40%;
  }
}

@media (prefers-reduced-motion: reduce) {
  *,
  *::before,
  *::after {
    animation: none !important;
    transition: none !important;
  }
}
)=====";

static const char INDEX_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="theme-color" content="#ffffff">
  <title>ESPRouter &ndash; Status</title>
  <link rel="icon" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Crect width='32' height='32' fill='%230b0d0f'/%3E%3Cpath d='M16 27V14' stroke='%2300e5ff' stroke-width='2'/%3E%3Ccircle cx='16' cy='12' r='2.2' fill='%2300e5ff'/%3E%3Cpath d='M10 8a8 8 0 0 1 12 0M7 4.5a12.5 12.5 0 0 1 18 0' stroke='%2300e5ff' stroke-width='2' fill='none'/%3E%3C/svg%3E">
  <link rel="preload" href="/fonts/share-tech-mono-400.woff2" as="font" type="font/woff2" crossorigin>
  <link rel="stylesheet" href="/style.css">
</head>
<body>

<header>
  <div class="header-left">
    <div class="brand-copy">
      <div class="brand-line">
        <h1>ESPRouter</h1>
        <span class="version-tag">v1.0</span>
      </div>
      <p class="brand-eyebrow"><span>//</span> ESP8266 ACCESS POINT</p>
    </div>
  </div>
  <nav>
    <a href="/" class="active">Status</a>
    <a href="/config">Configuration</a>
  </nav>
  <div class="scroll-progress" id="scrollProgress" aria-hidden="true"></div>
</header>

<main>
  <div class="hero">
    <p class="hero-eyebrow">// WIRELESS OVERVIEW</p>
    <h2>Access Point</h2>
    <div class="call">ESPRouter</div>
    <p class="subtitle">Access Point &middot; DHCP &middot; 2.4 GHz</p>
  </div>

  <section>
    <p class="section-eyebrow"><span>//</span> LIVE TELEMETRY</p>
    <h2>System Status</h2>
    <div class="time-grid">
      <div class="time-card">
        <span class="time-label">Uptime</span>
        <span class="time-value" id="uptime">--:--:--</span>
        <span class="time-zone">since boot</span>
      </div>
      <div class="time-card">
        <span class="time-label">Free Heap</span>
        <span class="time-value" id="heap">--</span>
        <span class="time-zone">KB</span>
      </div>
      <div class="time-card">
        <span class="time-label">Clients</span>
        <span class="time-value" id="clients">--</span>
        <span class="time-zone">connected</span>
      </div>
    </div>
    <p class="time-hint" id="lastUpdate">Live updates every 5 seconds.</p>
  </section>

  <div class="grid-2">
    <section>
      <p class="section-eyebrow"><span>//</span> NETWORK</p>
      <h2>Network</h2>
      <table class="data-table">
        <tbody>
          <tr><th>SSID</th><td id="ssid">&ndash;</td></tr>
          <tr><th>IP Address</th><td id="ip">&ndash;</td></tr>
          <tr><th>MAC (AP)</th><td id="mac">&ndash;</td></tr>
          <tr><th>Channel</th><td id="channel">&ndash;</td></tr>
          <tr><th>Hidden</th><td id="hidden">&ndash;</td></tr>
          <tr><th>Security</th><td id="security">&ndash;</td></tr>
          <tr><th>DHCP</th><td>active (automatic)</td></tr>
        </tbody>
      </table>
    </section>
    <section>
      <p class="section-eyebrow"><span>//</span> DEVICE</p>
      <h2>Device</h2>
      <table class="data-table">
        <tbody>
          <tr><th>Chip-ID</th><td id="chipId">&ndash;</td></tr>
          <tr><th>CPU</th><td id="cpu">&ndash;</td></tr>
          <tr><th>Flash</th><td id="flash">&ndash;</td></tr>
          <tr><th>SDK</th><td id="sdk">&ndash;</td></tr>
          <tr><th>Core</th><td id="core">&ndash;</td></tr>
          <tr><th>Reset</th><td id="reset">&ndash;</td></tr>
        </tbody>
      </table>
    </section>
  </div>

  <section>
    <p class="section-eyebrow"><span>//</span> CLIENTS</p>
    <h2>Connected Devices</h2>
    <div class="table-wrap">
      <table class="data-table">
        <thead>
          <tr><th>MAC Address</th><th>IP Address</th></tr>
        </thead>
        <tbody id="stationList">
          <tr><td colspan="2" class="muted">Loading ...</td></tr>
        </tbody>
      </table>
    </div>
    <p class="hint">The ESP8266 assigns addresses automatically via DHCP.</p>
  </section>
</main>

<footer>
  <p>ESPRouter v1.0 &middot; ESP8266 Access Point</p>
</footer>

<script src="/app.js"></script>
</body>
</html>
)=====";

static const char CONFIG_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta name="theme-color" content="#ffffff">
  <title>ESPRouter &ndash; Configuration</title>
  <link rel="icon" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Crect width='32' height='32' fill='%230b0d0f'/%3E%3Cpath d='M16 27V14' stroke='%2300e5ff' stroke-width='2'/%3E%3Ccircle cx='16' cy='12' r='2.2' fill='%2300e5ff'/%3E%3Cpath d='M10 8a8 8 0 0 1 12 0M7 4.5a12.5 12.5 0 0 1 18 0' stroke='%2300e5ff' stroke-width='2' fill='none'/%3E%3C/svg%3E">
  <link rel="preload" href="/fonts/share-tech-mono-400.woff2" as="font" type="font/woff2" crossorigin>
  <link rel="stylesheet" href="/style.css">
</head>
<body>

<header>
  <div class="header-left">
    <div class="brand-copy">
      <div class="brand-line">
        <h1>ESPRouter</h1>
        <span class="version-tag">v1.0</span>
      </div>
      <p class="brand-eyebrow"><span>//</span> ESP8266 ACCESS POINT</p>
    </div>
  </div>
  <nav>
    <a href="/">Status</a>
    <a href="/config" class="active">Configuration</a>
  </nav>
  <div class="scroll-progress" id="scrollProgress" aria-hidden="true"></div>
</header>

<main>
  <div class="hero hero-small">
    <p class="hero-eyebrow">// CONFIGURATION</p>
    <h2>Configuration</h2>
    <div class="call">CONFIG</div>
    <p class="subtitle">Set up or change the access point</p>
  </div>

  <section>
    <p class="section-eyebrow"><span>//</span> ACCESS POINT</p>
    <h2>Access Point</h2>
    %SETUPNOTICE%
    %ERROR%
    %NOTICE%
    <form method="post" action="/save" autocomplete="off">
      <div class="field">
        <label for="ssid">Wi-Fi Name (SSID)</label>
        <input id="ssid" name="ssid" type="text" maxlength="31" required value="%SSID%" placeholder="My network">
        <p class="hint">1 to 31 characters.</p>
      </div>
      <div class="field">
        <label for="pass">Wi-Fi Password</label>
        <input id="pass" name="pass" type="password" minlength="8" maxlength="63" value="" placeholder="empty = open network">
        <p class="hint">Leave empty for an open network, otherwise 8 to 63 characters. Saving an empty field removes an existing password. Current: <strong>%PASSSTATE%</strong></p>
      </div>
      <div class="field-grid">
        <div class="field">
          <label for="channel">Wi-Fi Channel</label>
          <select id="channel" name="channel">%CHANNEL_OPTIONS%</select>
          <p class="hint">Automatic picks the least busy channel at boot. Manual: 1 to 13; channels 1, 6 and 11 usually overlap the least.</p>
        </div>
        <div class="field">
          <label for="maxClients">Maximum Clients</label>
          <select id="maxClients" name="maxClients">%CLIENTS_OPTIONS%</select>
          <p class="hint">1 to 4 simultaneous devices.</p>
        </div>
      </div>
      <label class="checkbox-field" for="hidden">
        <input id="hidden" name="hidden" type="checkbox" value="1" %HIDDEN_CHECKED%>
        <span>
          <span class="checkbox-title">Hide Wi-Fi network</span>
          <span class="hint">The SSID is not actively broadcast and must be added manually on the client.</span>
        </span>
      </label>
      <div class="form-actions">
        <button class="btn" type="submit">Save &amp; Restart</button>
        %BACKLINK%
      </div>
    </form>
  </section>

  <section>
    <p class="section-eyebrow"><span>//</span> SYSTEM</p>
    <h2>Restart</h2>
    <p>Restarts the ESP8266 without changing the settings.</p>
    <form method="post" action="/reboot" onsubmit="return confirm('Restart the ESP8266 now?')">
      <button class="btn btn-secondary" type="submit">Restart Now</button>
    </form>
  </section>

  <section class="danger-zone">
    <p class="section-eyebrow"><span>//</span> FACTORY RESET</p>
    <h2>Factory Reset</h2>
    <p>Deletes all settings. The ESP8266 then restarts in open setup mode with a new setup Wi-Fi network.</p>
    <form method="post" action="/factory" onsubmit="return confirm('Really reset to factory defaults?')">
      <button class="btn btn-danger" type="submit">Factory Reset</button>
    </form>
  </section>
</main>

<footer>
  <p>ESPRouter v1.0 &middot; ESP8266 Access Point</p>
  <p class="footer-muted">Any connected client can change these settings.</p>
</footer>

<script src="/app.js"></script>
</body>
</html>
)=====";

static const char ACTION_HTML[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="refresh" content="8;url=/">
  <meta name="theme-color" content="#ffffff">
  <title>ESPRouter &ndash; Restart</title>
  <link rel="icon" href="data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 32 32'%3E%3Crect width='32' height='32' fill='%230b0d0f'/%3E%3Cpath d='M16 27V14' stroke='%2300e5ff' stroke-width='2'/%3E%3Ccircle cx='16' cy='12' r='2.2' fill='%2300e5ff'/%3E%3Cpath d='M10 8a8 8 0 0 1 12 0M7 4.5a12.5 12.5 0 0 1 18 0' stroke='%2300e5ff' stroke-width='2' fill='none'/%3E%3C/svg%3E">
  <link rel="preload" href="/fonts/share-tech-mono-400.woff2" as="font" type="font/woff2" crossorigin>
  <link rel="stylesheet" href="/style.css">
</head>
<body>
<header>
  <div class="header-left">
    <div class="brand-copy">
      <div class="brand-line">
        <h1>ESPRouter</h1>
        <span class="version-tag">v1.0</span>
      </div>
      <p class="brand-eyebrow"><span>//</span> ESP8266 ACCESS POINT</p>
    </div>
  </div>
  <nav>
    <a href="/">Status</a>
    <a href="/config">Configuration</a>
  </nav>
  <div class="scroll-progress" id="scrollProgress" aria-hidden="true"></div>
</header>
<main>
  <section>
    <p class="section-eyebrow"><span>//</span> SYSTEM</p>
    <h2>Restart</h2>
    <p>%MESSAGE%</p>
    <p class="hint">The Wi-Fi connection will briefly disconnect. This page reloads in a few seconds.</p>
    <p><a class="btn" href="/">View Status</a></p>
  </section>
</main>
<footer>
  <p>ESPRouter v1.0 &middot; ESP8266 Access Point</p>
</footer>
<script src="/app.js"></script>
</body>
</html>
)=====";

static const char APP_JS[] PROGMEM = R"=====(
(function () {
  'use strict';

  var scrollProgress = document.getElementById('scrollProgress');

  function updateScrollProgress() {
    if (!scrollProgress) return;
    var root = document.documentElement;
    var max = root.scrollHeight - root.clientHeight;
    scrollProgress.style.width = max > 0 ? Math.min(100, (root.scrollTop / max) * 100) + '%' : '0%';
  }

  if (scrollProgress) {
    window.addEventListener('scroll', updateScrollProgress, { passive: true });
    window.addEventListener('resize', updateScrollProgress);
    window.addEventListener('load', updateScrollProgress);
    updateScrollProgress();
  }

  function pad(n) {
    return n < 10 ? '0' + n : '' + n;
  }

  function formatUptime(total) {
    var s = Math.max(0, Math.floor(total));
    var d = Math.floor(s / 86400);
    var h = Math.floor((s % 86400) / 3600);
    var m = Math.floor((s % 3600) / 60);
    var sec = s % 60;
    return (d > 0 ? d + 'd ' : '') + pad(h) + ':' + pad(m) + ':' + pad(sec);
  }

  function setText(id, value) {
    var el = document.getElementById(id);
    if (el) el.textContent = value;
  }

  function renderStations(stations) {
    var tbody = document.getElementById('stationList');
    if (!tbody) return;
    if (!stations || stations.length === 0) {
      tbody.innerHTML = '<tr><td colspan="2" class="muted">No devices connected</td></tr>';
      return;
    }
    var html = '';
    for (var i = 0; i < stations.length; i++) {
      html += '<tr><td>' + stations[i].mac + '</td><td>' + stations[i].ip + '</td></tr>';
    }
    tbody.innerHTML = html;
  }

  function refreshStatus() {
    if (!document.getElementById('uptime')) return;
    fetch('/api/status', { cache: 'no-store' })
      .then(function (response) {
        if (!response.ok) throw new Error('HTTP ' + response.status);
        return response.json();
      })
      .then(function (d) {
        setText('uptime', formatUptime(d.uptime));
        setText('heap', Math.round(d.freeHeap / 1024));
        setText('clients', d.clients + ' / ' + d.maxClients);
        setText('ssid', d.ssid);
        setText('ip', d.ip);
        setText('mac', d.mac);
        setText('channel', d.channel);
        setText('hidden', d.hidden ? 'Yes' : 'No');
        setText('security', d.security);
        setText('chipId', d.chipId);
        setText('cpu', d.cpuMhz + ' MHz');
        setText('flash', d.flashKb + ' KB');
        setText('sdk', d.sdk);
        setText('core', d.core);
        setText('reset', d.reset);
        renderStations(d.stationList);
        setText('lastUpdate', 'Last update: ' + new Date().toLocaleTimeString('en-GB'));
      })
      .catch(function () {
        setText('lastUpdate', 'Connection to ESP8266 lost - retrying ...');
      });
  }

  refreshStatus();
  setInterval(refreshStatus, 5000);
})();
)=====";
