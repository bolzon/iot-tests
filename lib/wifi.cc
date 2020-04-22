#include "wifi.h"

Wifi::Wifi(const char* ssid, const char* pwd) {
  m_ssid = ssid;
  m_pwd = pwd;
  m_pIp = 0;
  m_pGateway = 0;
  m_pSubnet = 0;
}

Wifi(const char* ssid, const char* pwd, IPAddress* ip, IPAddress* gateway, IPAddress* subnet) : Wifi(ssid, pwd) {
  m_pIp = ip;
  m_pGateway = gateway;
  m_pSubnet = subnet;
}

Wifi::~Wifi() {}

bool Wifi::connect() {
  if (this->isConnected()) {
    return true;
  }
  WiFi.mode(WIFI_STA);
  if (m_pIp != 0) {
    WiFi.config(localip, gateway, subnet);
  }
  WiFi.begin(ssid, pwd);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    return false;
  }
  return true;
}

bool Wifi::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}
