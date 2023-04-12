#include <Arduino.h>
#include <WiFi.h>

#include "OneButton.h"
#include "DrawPaper.h"

#define button_pin_1 8
OneButton button(button_pin_1, true);

void attachClick()
{
  Serial.println("click-单击");
  drawPapers();
  // partialDraw();
}

// 按下多次
void attachMultiClick()
{
  Serial.printf("getNumberClicks-总共按了：%d次。\r\n", button.getNumberClicks());
  if (button.getNumberClicks() > 5)
  {
    Serial.println("停止 wifi 连接并删除保存的wifi信息");
    WiFi.disconnect(true, true); // 停止 wifi 连接并删除保存的wifi信息
  }
}

// 不断检测按钮按下状态
void tick()
{
  button.tick();
}

void button_event_init()
{
  Serial.println("button_event_init");
  button.reset(); // 清除按钮状态机的状态

  button.attachClick(attachClick);           // 初始化单击回调函数
  button.attachMultiClick(attachMultiClick); // 初始化按了多次(3次或以上)回调函数
}
