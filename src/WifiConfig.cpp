#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>
#include "DrawPaper.h"

Preferences preferences;
String ssid;
String password;

void initSmartConnecting()
{
  WiFi.mode(WIFI_AP_STA);
  if (!WiFi.beginSmartConfig())
  {
    Serial.println("beginSmartConfig error.");
    return;
  }

  Serial.println("Waiting for SmartConfig.");
  while (!WiFi.smartConfigDone())
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("SmartConfig received.");

  Serial.println("Waiting for WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  preferences.begin("wifi", false);
  preferences.putString("ssid", WiFi.SSID());
  preferences.putString("password", WiFi.psk());
  preferences.end();
  Serial.println("Store ssid & password in Flash");

  ESP.restart();
}

void wifiConnect()
{
  preferences.begin("wifi", false);
  ssid = preferences.getString("ssid", "none");
  password = preferences.getString("password", "none");
  Serial.println(ssid);
  Serial.println(password);
  preferences.end();

  WiFi.begin(ssid.c_str(), password.c_str());
  delay(500);

  int count = 0;
  do
  {
    if (count > 20)
    {
      drawSmartConfigInfo2User();
      initSmartConnecting();
    }

    delay(1000);
    count++;

    Serial.print(".");
  } while (WiFi.status() != WL_CONNECTED);

  Serial.println("WiFi Connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  drawWifiInfo2User(WiFi.localIP().toString());
  delay(1000);
}