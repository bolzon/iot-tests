/*
 * Connecting to a MQTT broker using ESP8266 (ESP12)
 * Alexandre Bolzon <blzn@mail.ru>
 * April 2020
 */

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

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

// mqtt params

#define MQTT_ID "esp8266"
#define MQTT_PUB "bolzon_pub"
#define MQTT_SUB "bolzon_sub"

const char* MQTT_BROKER_URL = "192.168.0.177";
const int MQTT_BROKER_PORT = 1883;

WiFiClient wifi_client;
void mqtt_callback(const char*, byte*, unsigned int);
PubSubClient mqtt_client(MQTT_BROKER_URL, MQTT_BROKER_PORT, mqtt_callback, wifi_client);

byte mqtt_data = 0; // 0 or 1 (off/on)

// wifi params

IPAddress localip(192, 168, 0, 77);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

const char* ssid = "";
const char* pwd = "";

void init_wifi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;
  }

  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.hostname("esp8266");
  WiFi.config(localip, gateway, subnet);
  WiFi.begin(ssid, pwd);

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Error connecting to wifi");
    Serial.println("Rebooting in 5 secs...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Connected to wifi!");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());
}

void init_mqtt() {
  while (!mqtt_client.connected()) {
    Serial.printf("Connecting to MQTT broker: %s\n", MQTT_BROKER_URL);

    if (mqtt_client.connect(MQTT_ID)) {
      Serial.println("Connected to MQTT broker!");
      if (mqtt_client.subscribe(MQTT_SUB)) {
        Serial.printf("Successfully subscribed to \"%s\"\n", MQTT_SUB);
      }
      else {
        Serial.printf("Could not subscribe to \"%s\"\n", MQTT_SUB);
      }
    }
    else {
      Serial.println("Error connecting to MQTT broker");
      Serial.println("Retrying in 3 secs");
      delay(3000);
    }
  }
}

void mqtt_callback(const char* topic, byte* payload, unsigned int length) {
  Serial.printf("%s MQTT callback\n", MQTT_SUB);
  if (length == 0) {
    return;
  }
  const byte data = (byte)(payload[0] - '0');
  Serial.printf("Payload: \"%d\"\n", data);
  if (data == 1 || data == 0) {
    mqtt_data = data;
  }
  Serial.printf("MQTT data: \"%d\"\n", (int)mqtt_data);
  update_io();
  mqtt_pub();
}

void update_io() {
  // here you can update your IO
  // according to MQTT data received/set
  // e.g.

  const int pin = D0;
  const int signal = mqtt_data ? HIGH : LOW;

  Serial.printf("digitalWrite(%d, %s)\n", pin, signal ? "HIGH" : "LOW");
  digitalWrite(pin, signal);
}

void mqtt_pub() {
  const char* msg = mqtt_data ? "1" : "0";
  Serial.printf("Publishing MQTT data: %s\n", msg);
  mqtt_client.publish(MQTT_PUB, msg);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Initializing");

  init_wifi();
  init_mqtt();

  update_io();
  mqtt_pub();
}

void loop() {
  delay(1000);
  if (!mqtt_client.loop()) {
    init_mqtt();
  }
}
