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

IPAddress localip(192, 168, 0, 77);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const int relay_pin = D1;
const char* ssid = "";
const char* pwd = "";

ESP8266WebServer server(80);

void ok() {
  static char* html = "" \
    "<html lang=\"en-US\">" \
    "<head>" \
    "<title>Relay control</title>" \
    "<script src=\"https://code.jquery.com/jquery-3.5.0.min.js\"></script>" \
    "</head>" \
    "<body>" \
    "<script>" \
    "var baseurl = 'http://192.168.0.77/';" \
    "function call(action) {" \
    "  $.get(baseurl + action, function() {});" \
    "}" \
    "</script>" \
    "<h3>Relay</h3>" \
    "<button onclick=\"call('on')\">On</button> " \
    "<button onclick=\"call('off')\">Off</button> " \
    "<button onclick=\"call('pulse')\">Pulse</button>" \
    "</body>" \
    "</html>";

  Serial.println("GET /ok");
  server.send(200, "text/html", html);
}

void not_found() {
  Serial.println("Not found");
  server.send(404, "text/html", "Not found");
}

void pulse() {
  Serial.println("GET /pulse");
  digitalWrite(relay_pin, LOW);
  delay(1000);
  digitalWrite(relay_pin, HIGH);
  server.send(200, "text/html", "Pulsed");
}

void init_wifi() {
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname("esp8266");
  WiFi.config(localip, gateway, subnet);
  WiFi.begin(ssid, pwd);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Wifi connection failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.print("Wifi connected! Local IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

void init_server() {
  server.on("/", ok);
  server.on("/pulse", pulse);

  server.on("/on", []() {
    Serial.println("GET /on");
    digitalWrite(relay_pin, HIGH);
    server.send(200, "text/html", "On");
  });

  server.on("/off", []() {
    Serial.println("GET /off");
    digitalWrite(relay_pin, LOW);
    server.send(200, "text/html", "Off");
  });

  server.onNotFound(not_found);
  server.begin();

  Serial.println("Server listening");
}

void setup() {
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, HIGH);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing");

  init_wifi();
  init_server();
}

void loop() {
  server.handleClient();
}
