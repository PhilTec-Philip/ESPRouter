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

*,
*::before,
*::after {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  border-radius: 0;
}

html {
  color-scheme: light;
  background: #ffffff;
  scroll-behavior: smooth;
}

body {
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  background: #ffffff;
  color: #111111;
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
  background: #111111;
}

::-webkit-scrollbar-thumb:hover {
  background: #007a8f;
}

a:focus-visible,
button:focus-visible,
input:focus-visible,
select:focus-visible,
label:has(input:focus-visible) {
  outline: 2px dashed #007a8f;
  outline-offset: 2px;
}

::selection {
  background: #007a8f;
  color: #0c0f11;
}

header {
  position: sticky;
  top: 0;
  z-index: 999;
  background: #ffffff;
  border-bottom: 1px solid #111111;
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
  background: #007a8f;
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
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1.35rem;
  color: #000000;
  font-weight: 400;
  letter-spacing: 2px;
  text-transform: uppercase;
  line-height: 1.1;
}

.brand-eyebrow {
  margin-top: 0.18rem;
  color: #444444;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 0.68rem;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.brand-eyebrow span {
  color: #007a8f;
}

.version-tag {
  display: inline-block;
  padding: 0.12rem 0.45rem;
  border: 1px solid #007a8f;
  color: #007a8f;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
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
  color: #444444;
  text-decoration: none;
  padding: 0.45rem 0.9rem;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
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
  color: #000000;
}

nav a.active {
  background: rgba(127, 127, 127, 0.12);
  color: #000000;
  font-weight: 700;
  box-shadow: inset 0 -2px 0 #007a8f;
}

main {
  flex: 1;
  max-width: 1120px;
  width: 100%;
  margin: 2.5rem auto 0;
  padding: 0 2rem 2.5rem;
  background: #ffffff;
}

.hero {
  text-align: center;
  padding: 3rem 2rem;
  background: #ffffff;
  margin-bottom: 2rem;
  border: 1px solid #111111;
  box-shadow: 4px 4px 0 rgba(0, 0, 0, 0.15);
  position: relative;
  overflow: hidden;
}

.hero-small {
  padding: 2rem;
}

.hero-eyebrow,
.section-eyebrow {
  color: #666666;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 0.72rem;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.hero-eyebrow {
  color: #007a8f;
  margin-bottom: 0.75rem;
}

.section-eyebrow {
  margin: -0.2rem 0 0.15rem;
}

.section-eyebrow span {
  color: #007a8f;
}

.hero h2 {
  color: #111111;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
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
  color: #007a8f;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1.8rem;
  font-weight: 400;
  border: 1px solid #111111;
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
  color: #444444;
  font-size: 1.05rem;
  font-weight: 400;
  letter-spacing: 1px;
  margin-top: 0.5rem;
}

section {
  position: relative;
  background: #ffffff;
  padding: 2rem;
  margin-bottom: 1.5rem;
  border: 1px solid #111111;
  box-shadow: 4px 4px 0 rgba(0, 0, 0, 0.15);
}

section:hover {
  box-shadow: 5px 5px 0 rgba(0, 0, 0, 0.25);
}

section h2 {
  color: #000000;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1.3rem;
  margin-bottom: 1rem;
  padding-bottom: 0.6rem;
  border-bottom: 1px solid #111111;
  font-weight: 400;
  letter-spacing: 1px;
  text-transform: uppercase;
}

section h2::before {
  content: '[ ';
  color: #007a8f;
}

section h2::after {
  content: ' ]';
  color: #007a8f;
}

section h3 {
  color: #222222;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1.02rem;
  margin: 1.5rem 0 0.75rem;
  font-weight: 400;
  letter-spacing: 0.5px;
}

section h3::before {
  content: '// ';
  color: #007a8f;
}

p {
  margin-bottom: 0.75rem;
}

a {
  color: #007a8f;
  text-decoration: none;
  border-bottom: 1px dashed transparent;
  transition: color 0.08s linear, border-color 0.08s linear;
}

a:hover {
  color: #005b6b;
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
  background: #007a8f;
  color: #0c0f11;
  border: 1px solid #007a8f;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 0.82rem;
  font-weight: 700;
  text-transform: uppercase;
  letter-spacing: 1px;
  text-decoration: none;
  box-shadow: 3px 3px 0 rgba(0, 0, 0, 0.15);
  cursor: pointer;
  transition: background 0.08s linear, color 0.08s linear, box-shadow 0.08s linear, border-color 0.08s linear;
}

.btn:hover {
  background: transparent;
  color: #007a8f;
  border-color: #007a8f;
  box-shadow: 4px 4px 0 rgba(0, 0, 0, 0.25);
}

.btn:active {
  transform: translate(2px, 2px);
  box-shadow: none;
}

.btn-secondary {
  background: transparent;
  color: #111111;
  border-color: #111111;
}

.btn-secondary:hover {
  color: #007a8f;
  border-color: #007a8f;
}

.btn-danger {
  background: transparent;
  color: #b3261e;
  border-color: #b3261e;
}

.btn-danger:hover {
  background: #b3261e;
  color: #ffffff;
  border-color: #b3261e;
}

.time-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(170px, 1fr));
  gap: 0;
  margin-top: 1rem;
  background: #cbd5e1;
  border: 1px solid #111111;
  box-shadow:
    inset 0 0 0 1px #000,
    inset 0 0 28px rgba(0, 0, 0, 0.65),
    4px 4px 0 rgba(0, 0, 0, 0.15);
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
  border-right: 1px dashed rgba(0, 122, 143, 0.25);
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
  color: #444444;
  margin-bottom: 0.4rem;
}

.time-card .time-value {
  display: block;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1.7rem;
  font-weight: 400;
  color: #000000;
  text-shadow:
    0 0 6px rgba(0, 122, 143, 0.1),
    0 0 18px rgba(0, 122, 143, 0.1);
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
  color: #444444;
  letter-spacing: 1px;
  margin-top: 0.3rem;
}

.time-hint {
  margin-top: 1rem;
  font-size: 0.78rem;
  color: #666666;
}

.time-hint::before {
  content: '// ';
  color: #007a8f;
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
  border: 1px solid #111111;
}

.data-table th {
  background: #ffffff;
  color: #444444;
  padding: 0.5rem 0.75rem;
  text-align: left;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-weight: 700;
  font-size: 0.75rem;
  text-transform: uppercase;
  letter-spacing: 1px;
  border-bottom: 1px solid #111111;
}

.data-table td {
  padding: 0.4rem 0.75rem;
  border-bottom: 1px solid #111111;
  word-break: break-word;
}

.data-table tr:last-child td {
  border-bottom: none;
}

.data-table tr:nth-child(even) td {
  background: #f8f9fa;
}

.data-table th:first-child {
  width: 36%;
}

.hint,
.muted {
  font-size: 0.78rem;
  color: #666666;
}

.field {
  margin-bottom: 1.25rem;
}

.field label {
  display: block;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 0.85rem;
  letter-spacing: 1px;
  text-transform: uppercase;
  margin-bottom: 0.4rem;
  color: #222222;
}

.field label::before {
  content: '// ';
  color: #007a8f;
}

.field input,
.field select {
  width: 100%;
  max-width: 520px;
  padding: 0.7rem 0.85rem;
  background: #ffffff;
  border: 1px solid #111111;
  color: #111111;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 1rem;
  outline: none;
  transition: border-color 0.08s linear, box-shadow 0.08s linear;
}

.field select {
  cursor: pointer;
}

.field input:focus,
.field select:focus {
  border-color: #007a8f;
  box-shadow: 3px 3px 0 rgba(0, 122, 143, 0.1);
}

.field input::placeholder {
  color: #666666;
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
  border: 1px solid #111111;
  background: #f8f9fa;
  cursor: pointer;
  transition: border-color 0.08s linear, background 0.08s linear, box-shadow 0.08s linear;
}

.checkbox-field:hover {
  border-color: #007a8f;
  background: #ffffff;
  box-shadow: 3px 3px 0 rgba(0, 0, 0, 0.15);
}

.checkbox-field input[type="checkbox"] {
  width: 1.05rem;
  height: 1.05rem;
  margin-top: 0.25rem;
  accent-color: #007a8f;
  flex-shrink: 0;
  cursor: pointer;
}

.checkbox-field input[type="checkbox"]:focus-visible {
  outline: 2px dashed #007a8f;
  outline-offset: 2px;
}

.checkbox-field .checkbox-title {
  display: block;
  font-family: 'Share Tech Mono', Consolas, 'Courier New', monospace;
  font-size: 0.85rem;
  letter-spacing: 1px;
  text-transform: uppercase;
  color: #222222;
}

.checkbox-field .checkbox-title::before {
  content: '// ';
  color: #007a8f;
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
  border: 1px solid #007a8f;
  background: rgba(0, 122, 143, 0.1);
  color: #111111;
  font-size: 0.85rem;
}

.notice::before {
  content: '// ';
  color: #007a8f;
}

.error {
  border-color: #b3261e;
  background: rgba(179, 38, 30, 0.08);
  color: #b3261e;
}

.error::before {
  content: '!! ';
}

.danger-zone {
  border-color: #b3261e;
}

.danger-zone h2 {
  color: #b3261e;
  border-bottom-color: #b3261e;
}

.danger-zone h2::before,
.danger-zone h2::after {
  color: #b3261e;
}

footer {
  background: #ffffff;
  border-top: 1px solid #111111;
  text-align: center;
  padding: 1.25rem;
  font-size: 0.82rem;
  color: #666666;
  letter-spacing: 0.3px;
}

footer p {
  margin: 0.3rem 0;
}

footer a {
  color: #111111;
  border-bottom-color: transparent;
}

footer a:hover {
  color: #007a8f;
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
    border-bottom: 1px dashed rgba(0, 122, 143, 0.25);
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
    border-top: 1px solid #111111;
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
        <span class="version-tag">v1.1</span>
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
          <tr><th>Hostname</th><td>esprouter.local</td></tr>
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
          <tr><th>Name</th><th>MAC Address</th><th>IP Address</th></tr>
        </thead>
        <tbody id="stationList">
          <tr><td colspan="3" class="muted">Loading ...</td></tr>
        </tbody>
      </table>
    </div>
    <p class="hint">The ESP8266 assigns addresses automatically via DHCP.</p>
  </section>
</main>

<footer>
  <p>ESPRouter v1.1 &middot; ESP8266 Access Point</p>
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
        <span class="version-tag">v1.1</span>
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

  <form method="post" action="/save" autocomplete="off">
    <section>
      <p class="section-eyebrow"><span>//</span> ACCESS POINT</p>
      <h2>Access Point</h2>
      %SETUPNOTICE%
      %ERROR%
      %NOTICE%
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
    </section>

    <section>
      <p class="section-eyebrow"><span>//</span> SECURITY</p>
      <h2>Admin Access</h2>
      <p>Optionally require a browser login before the configuration can be viewed or changed. The status page stays public.</p>
      <label class="checkbox-field" for="adminEnabled">
        <input id="adminEnabled" name="adminEnabled" type="checkbox" value="1" %ADMIN_CHECKED%>
        <span>
          <span class="checkbox-title">Require login for settings</span>
          <span class="hint">Protects configuration, saving, client names, restart, and factory reset.</span>
        </span>
      </label>
      <div class="field">
        <label for="adminPass">Admin Password</label>
        <input id="adminPass" name="adminPass" type="password" maxlength="63" value="" placeholder="empty = keep current">
        <p class="hint">Username: <strong>admin</strong>. Password: 8 to 63 characters. Leave empty to keep the current password. Disable the checkbox to remove protection. Current: <strong>%ADMINSTATE%</strong></p>
      </div>
      <div class="form-actions">
        <button class="btn" type="submit">Save &amp; Restart</button>
        %BACKLINK%
      </div>
    </section>
  </form>

  <section>
    <p class="section-eyebrow"><span>//</span> CLIENTS</p>
    <h2>Client Names</h2>
    <p>Assign friendly names to connected or previously seen devices. Names are stored by MAC address and shown on the status page.</p>
    <form method="post" action="/names" autocomplete="off">
      %NAMEROWS%
      <div class="form-actions">
        <button class="btn btn-secondary" type="submit">Save Names</button>
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
  <p>ESPRouter v1.1 &middot; ESP8266 Access Point</p>
  <p class="footer-muted">Settings can be protected with an optional admin login.</p>
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
        <span class="version-tag">v1.1</span>
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
  <p>ESPRouter v1.1 &middot; ESP8266 Access Point</p>
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

  function escapeHtml(value) {
    return String(value == null ? '' : value)
      .replace(/&/g, '&amp;')
      .replace(/</g, '&lt;')
      .replace(/>/g, '&gt;')
      .replace(/"/g, '&quot;')
      .replace(/'/g, '&#39;');
  }

  function renderStations(stations) {
    var tbody = document.getElementById('stationList');
    if (!tbody) return;
    if (!stations || stations.length === 0) {
      tbody.innerHTML = '<tr><td colspan="3" class="muted">No devices connected</td></tr>';
      return;
    }
    var html = '';
    for (var i = 0; i < stations.length; i++) {
      var name = stations[i].name ? escapeHtml(stations[i].name) : '&ndash;';
      html += '<tr><td>' + name + '</td><td>' + escapeHtml(stations[i].mac) +
        '</td><td>' + escapeHtml(stations[i].ip) + '</td></tr>';
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
