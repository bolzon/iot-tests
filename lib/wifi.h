#ifndef __WIFI_H__
#define __WIFI_H__

#include <ESP8266WiFi.h>

class Wifi {
public:

  Wifi(const char* ssid, const char* pwd);
  Wifi(const char* ssid, const char* pwd, IPAddress* ip, IPAddress* gateway, IPAddress* subnet);
  virtual ~Wifi();

  bool connect();
  bool isConnected();

private:

  String m_ssid;
  String m_pwd;

  IPAddress* m_gIp;
  IPAddress* m_pGateway;
  IPAddress* m_pSubnet;
};

#endif
