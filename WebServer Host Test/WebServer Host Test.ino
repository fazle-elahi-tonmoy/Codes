#include <WiFi.h>
const char* ssid = "The Tiny Bear";
const char* password = "bolajabena";

int ledpin = 13;  // D4 in ModeMcu
WiFiServer server(80);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.print(WiFi.localIP());
}

void loop() {
  client = server.available();
  if (!client) return;
  Serial.println("new client");
  while (!client.available()) delay(1);

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int value = LOW;
  if (request.indexOf(" /LED=ON") != -1) {
    digitalWrite(ledpin, 1);
    value = HIGH;
  }

  if (request.indexOf(" /LED=OFF") != -1) {
    digitalWrite(ledpin, 0);
    value = LOW;
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");  // do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<title>switch</title>");
  client.print("Led pin is now: ");
  (value == HIGH) ? client.print("OFF") : client.print("ON");
  client.println("<br><br>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn <b>ON</b></button></a>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn <b>OFF</b></button></a></br>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
