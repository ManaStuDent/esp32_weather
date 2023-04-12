#include <Arduino.h>
#include <Ticker.h>

#include "WifiConfig.h"
#include "Button.h"
#include "DrawPaper.h"

Ticker time1;

void setup()
{
  Serial.begin(115200);
  Serial.println("setup...");

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  wifiConnect();
  initDisplay();
  drawPapers(); // 开机后立马请求一次
  time1.attach(30 * 60, drawPapers);
  button_event_init();
}

void loop()
{
  tick();
}