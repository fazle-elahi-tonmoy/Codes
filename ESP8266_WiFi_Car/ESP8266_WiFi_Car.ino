/*
  ESP8266 Two-Wheel WiFi Robot (AP Mode, Web Controller) with animated FLIP toggle
  Updated: HTML now uses fullscreen viewport
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const uint8_t LEFT_INA_PIN = 13;
const uint8_t LEFT_INB_PIN = 15;
const uint8_t RIGHT_INC_PIN = 0;
const uint8_t RIGHT_IND_PIN = 2;
const bool LEFT_INVERT = false;
const bool RIGHT_INVERT = true;

const char *AP_SSID = "GEAR-GURUS";
const char *AP_PASS = "geargurus";
const IPAddress AP_IP(192, 168, 4, 1);
const IPAddress AP_GW(192, 168, 4, 1);
const IPAddress AP_MASK(255, 255, 255, 0);

ESP8266WebServer server(80);

void setLeftMotor(int dir) {
  if (LEFT_INVERT) dir = -dir;
  if (dir > 0) {
    digitalWrite(LEFT_INA_PIN, HIGH);
    digitalWrite(LEFT_INB_PIN, LOW);
  } else if (dir < 0) {
    digitalWrite(LEFT_INA_PIN, LOW);
    digitalWrite(LEFT_INB_PIN, HIGH);
  } else {
    digitalWrite(LEFT_INA_PIN, LOW);
    digitalWrite(LEFT_INB_PIN, LOW);
  }
}
void setRightMotor(int dir) {
  if (RIGHT_INVERT) dir = -dir;
  if (dir > 0) {
    digitalWrite(RIGHT_INC_PIN, HIGH);
    digitalWrite(RIGHT_IND_PIN, LOW);
  } else if (dir < 0) {
    digitalWrite(RIGHT_INC_PIN, LOW);
    digitalWrite(RIGHT_IND_PIN, HIGH);
  } else {
    digitalWrite(RIGHT_INC_PIN, LOW);
    digitalWrite(RIGHT_IND_PIN, LOW);
  }
}
void motor(int leftDir, int rightDir) {
  leftDir = (leftDir > 0) - (leftDir < 0);
  rightDir = (rightDir > 0) - (rightDir < 0);
  setLeftMotor(leftDir);
  setRightMotor(rightDir);
}

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no" />
    <title>GEAR GURUS Robot</title>
    <style>
        :root {
            --bg: #0e0f14;
            --accent: #00c2ff;
            --accent2: #4dfcc8;
            --text: #e9f0ff;
        }

        html,
        body {
            height: 100%;
            width: 100%;
            margin: 0;
            padding: 0;
            overflow: hidden;
        }

        body {
            font-family: system-ui, Segoe UI, Roboto, sans-serif;
            background: linear-gradient(160deg, #0b0d12, #161a28);
            color: var(--text);
            display: flex;
            align-items: center;
            justify-content: center;
        }

        .wrap {
            width: 100%;
            height: 100%;
            max-width: none;
            padding: 16px;
            display: flex;
            flex-direction: column;
        }

        .title {
            display: flex;
            justify-content: center;
            font-weight: 800;
            letter-spacing: .08em;
            margin-bottom: 12px;
            font-size: clamp(22px, 5vw, 40px);
        }

        .title span {
            background: linear-gradient(90deg, var(--accent), var(--accent2));
            -webkit-background-clip: text;
            color: transparent;
        }

        #fullscreenBtn {
            display: block;
            margin: 0 auto 16px auto;
            padding: 12px 24px;
            font-size: 18px;
            border-radius: 12px;
            background: var(--accent);
            color: #fff;
            border: none;
            cursor: pointer;
        }

        .controls {
            flex: 1;
            display: flex;
            justify-content: space-between;
            align-items: stretch;
            gap: 50px;
        }

        .leftCol {
            display: flex;
            flex-direction: column;
            justify-content: space-between;
            flex: 0 0 300px;
        }

        .rightCol {
            display: flex;
            flex-direction: row;
            justify-content: space-between;
            flex: 0 0 400px;
            gap: 32px;
            align-items: stretch;
        }

        .btn {
            flex: 1;
            margin: 8px;
            display: flex;
            align-items: center;
            justify-content: center;
            background: radial-gradient(120% 120% at 50% 0%, #1c2033, #121522);
            border: 2px solid rgba(255, 255, 255, .07);
            border-radius: 20px;
            padding: 24px;
            font-weight: 700;
            font-size: clamp(20px, 4.5vw, 30px);
            color: var(--text);
            box-shadow: 0 10px 20px rgba(0, 0, 0, .35), inset 0 0 0 0 rgba(0, 0, 0, 0);
            transition: transform .08s ease, box-shadow .12s ease, border-color .12s ease;
        }

        .btn:active,
        .btn.pressed {
            transform: translateY(2px) scale(.98);
            box-shadow: 0 4px 10px rgba(0, 0, 0, .5), inset 0 0 18px rgba(0, 0, 0, .35);
            border-color: rgba(255, 255, 255, .18);
        }

        .hint {
            opacity: .75;
            text-align: center;
            margin-top: 12px;
            font-size: 12px;
        }

        .flipToggle {
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            color: var(--text);
            font-weight: 700;
            letter-spacing: .05em;
            cursor: pointer;
            align-self: center;
        }

        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
        }

        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background: #ccc;
            transition: .4s;
            border-radius: 34px;
        }

        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background: white;
            transition: .4s;
            border-radius: 50%;
        }

        input:checked+.slider {
            background: var(--accent);
        }

        input:checked+.slider:before {
            transform: translateX(26px);
        }
    </style>
</head>

<body>
    <div class="wrap">
        <div class="title"><span>GEAR GURUS</span></div>
        <button id="fullscreenBtn">Enter Fullscreen</button>
        <div class="controls">
            <div class="leftCol">
                <div id="btnF" class="btn" data-key="F">Forward</div>
                <div id="btnB" class="btn" data-key="B">Backward</div>
            </div>
            <div class="flipToggle">
                <label>FLIP</label>
                <label class="switch"><input type="checkbox" id="flipSwitch"><span class="slider"></span></label>
            </div>
            <div class="rightCol">
                <div id="btnL" class="btn" data-key="L" style="flex:2;">Left</div>
                <div id="btnR" class="btn" data-key="R" style="flex:2;">Right</div>
            </div>
        </div>
        <div class="hint">Tap & hold. Releasing all buttons stops instantly.</div>
    </div>

    <script>
        (function () {
            const state = { F: false, B: false, L: false, R: false };
            let flip = false;
            let lastSent = '0,0';

            // ===== Fullscreen button =====
            const fsBtn = document.getElementById('fullscreenBtn');
            fsBtn.addEventListener('click', () => {
                const elem = document.documentElement;
                if (elem.requestFullscreen) elem.requestFullscreen();
                else if (elem.webkitRequestFullscreen) elem.webkitRequestFullscreen();
                else if (elem.msRequestFullscreen) elem.msRequestFullscreen();
                fsBtn.style.display = 'none'; // hide button after fullscreen
            });

            // ===== Robot control logic =====
            function decide() {
                let F = state.F, B = state.B, L = state.L, R = state.R;
                flip = document.getElementById('flipSwitch').checked;
                if (flip) { let tmp = L; L = R; R = tmp; tmp = F; F = B; B = tmp; }
                if ((F && B) || (L && R)) return [0, 0];
                if (F) { if (L) return [0, 1]; if (R) return [1, 0]; return [1, 1]; }
                if (B) { if (L) return [0, -1]; if (R) return [-1, 0]; return [-1, -1]; }
                if (L) {
                    if (flip) return [1, -1];
                    return [-1, 1];
                }
                if (R) {
                    if (flip) return [-1, 1];
                    return [1, -1];
                }
                return [0, 0];
            }

            function send(l, r) {
                const payload = `${l},${r}`;
                if (payload === lastSent) return;
                lastSent = payload;
                fetch(`/move?l=${l}&r=${r}`, { method: 'GET', cache: 'no-store', keepalive: true }).catch(() => { });
            }

            function update() { const [l, r] = decide(); send(l, r); }

            function setPressed(el, pressed) { el.classList.toggle('pressed', pressed); }

            function bind(btn) {
                const key = btn.dataset.key;
                const onPress = (e) => { e.preventDefault(); state[key] = true; setPressed(btn, true); update(); };
                const onRelease = (e) => { e.preventDefault(); state[key] = false; setPressed(btn, false); update(); };
                btn.addEventListener('touchstart', onPress, { passive: false });
                btn.addEventListener('touchend', onRelease, { passive: false });
                btn.addEventListener('touchcancel', onRelease, { passive: false });
                btn.addEventListener('mousedown', onPress);
                window.addEventListener('mouseup', onRelease);
                btn.addEventListener('mouseleave', (e) => { if (e.buttons === 1) onRelease(e); });
            }

            ['btnF', 'btnB', 'btnL', 'btnR'].forEach(id => bind(document.getElementById(id)));

        })();
    </script>
</body>

</html>
)rawliteral";

void handleRoot() {
  server.send_P(200, "text/html", INDEX_HTML);
}
void handleMove() {
  if (!server.hasArg("l") || !server.hasArg("r")) {
    server.send(400, "text/plain", "Missing args l,r");
    return;
  }
  int l = server.arg("l").toInt();
  int r = server.arg("r").toInt();
  if (l > 1) l = 1;
  if (l < -1) l = -1;
  if (r > 1) r = 1;
  if (r < -1) r = -1;
  motor(l, r);
  server.send(200, "text/plain", String("OK ") + l + "," + r);
}
void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}
void setupPins() {
  pinMode(LEFT_INA_PIN, OUTPUT);
  pinMode(LEFT_INB_PIN, OUTPUT);
  pinMode(RIGHT_INC_PIN, OUTPUT);
  pinMode(RIGHT_IND_PIN, OUTPUT);
  motor(0, 0);
}
void setupAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_IP, AP_GW, AP_MASK);
  WiFi.softAP(AP_SSID, AP_PASS);
}
void setupServer() {
  server.on("/", HTTP_GET, handleRoot);
  server.on("/move", HTTP_GET, handleMove);
  server.onNotFound(handleNotFound);
  server.begin();
}
void setup() {
  delay(200);
  setupPins();
  setupAP();
  setupServer();
}
void loop() {
  server.handleClient();
}