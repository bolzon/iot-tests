#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// nodemcu pins

#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15

const int relay_pin = D0;

const char* ssid = "ssid";
const char* pwd = "pwd";

ESP8266WebServer server(80);

void ok() {
  Serial.println("GET /ok");
  server.send(200, "text/html", "Ok");
}

void not_found() {
  server.send(404, "text/html", "Not found");
}

void activate_relay() {
  Serial.println("GET /relay");
  digitalWrite(relay_pin, LOW);
  delay(1000);
  digitalWrite(relay_pin, HIGH);
  server.send(200, "text/html", "Relay activated");
}

void setup() {
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing config/wifi...");

  WiFi.mode(WIFI_STA);
/*
  if (!WiFi.softAP(ssid, pwd)) {
    Serial.println("Could not connect to wifi");
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
*/
  WiFi.begin(ssid, pwd);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Wifi connection failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
/*
  if (!WiFi.softAPConfig(localip, gateway, subnet)) {
    Serial.println("Could not set wifi config");
  }
*/
  server.on("/", ok);
  server.on("/relay", activate_relay);

  server.on("/on", []() {
    digitalWrite(relay_pin, HIGH);
    server.send(200, "text/html", "On");
  });

  server.on("/off", []() {
    digitalWrite(relay_pin, LOW);
    server.send(200, "text/html", "Off");
  });

  server.onNotFound(not_found);
  server.begin();

  Serial.println("Server listening");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}
