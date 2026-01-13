/* ESP8266_GSheet_Bridge.ino
   Listens on Serial for lines beginning with "DATA:" followed by JSON.
   On receiving a JSON payload, POSTs it to the provided Google Apps Script webapp URL.
   WiFi SSID/Password are set to "ROBOTICS", "robotics" as requested.
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "ROBOTICS";
const char* password = "robotics";

// Paste your Apps Script Web App URL here (deployed as "Anyone, even anonymous" or "Anyone" depending on G Suite).
// Example: https://script.google.com/macros/s/AKfycbx.../exec
const char* WEBAPP_URL = "https://script.google.com/macros/s/AKfycbwKq8nOYv5iDjscjNtjspvaZT9OV4G8OQP1kbYMmIgBSRsaBZycJ-URkcWb7sI43WzH/exec";

WiFiClientSecure client;
HTTPClient https;

String incomingLine = "";

void setup() {
  Serial.begin(115200); // connected to Arduino Serial1 (Mega Serial1 <-> ESP's Serial)
  delay(10);
  Serial.println();
  Serial.println("ESP8266 Bridge starting...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned long start = millis();
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() - start > 15000) break; // 15s timeout
  }
  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi OK, IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("WiFi failed to connect (check credentials)");
  }

  // Allow insecure HTTPS (Apps Script uses valid certs; setInsecure used to simplify).
  client.setInsecure();
}

void loop() {
  // read from serial (line buffered)
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      processLine(incomingLine);
      incomingLine = "";
    } else if (c != '\r') {
      incomingLine += c;
      // avoid runaway buffer
      if (incomingLine.length() > 4000) incomingLine = incomingLine.substring(incomingLine.length()-4000);
    }
  }
}

void processLine(String line) {
  line.trim();
  if (line.length() == 0) return;

  // Expect prefix "DATA:"
  if (!line.startsWith("DATA:")) {
    // ignore other lines, but print for debug
    Serial.print("RX (ignored): ");
    Serial.println(line);
    return;
  }

  String json = line.substring(5); // remove "DATA:"
  json.trim();
  Serial.print("Received JSON: ");
  Serial.println(json);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, attempting reconnect...");
    WiFi.reconnect();
    delay(2000);
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Reconnect failed. Dropping payload.");
      return;
    }
  }

  // POST JSON to Google Apps Script
  Serial.println("POSTing to Apps Script...");
  https.begin(client, WEBAPP_URL); // HTTPS
  https.addHeader("Content-Type", "application/json");
  int httpResponseCode = https.POST(json);
  if (httpResponseCode > 0) {
    String resp = https.getString();
    Serial.print("HTTP ");
    Serial.print(httpResponseCode);
    Serial.print(" Response: ");
    Serial.println(resp);
  } else {
    Serial.print("Error on POST: ");
    Serial.println(httpResponseCode);
  }
  https.end();
}
