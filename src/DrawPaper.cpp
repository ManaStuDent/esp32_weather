#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>

#include "GxEPD2_BW.h"
#include "GxEPD2_3C.h"
#include "U8g2_for_Adafruit_GFX.h"
#include "ArduinoJson.h"
#include <Fonts/FreeMonoBold9pt7b.h>
#include "img_arr.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 60 * 60 * 8, 30 * 60 * 1000); // 北京时间

DynamicJsonDocument JSON_CAIYUN(50 * 1024);

GxEPD2_BW<GxEPD2_290_T5D, GxEPD2_290_T5D::HEIGHT> display(GxEPD2_290_T5D(/*CS=D8*/ SS, /*DC=D3*/ 10, /*RST=D4*/ 3, /*BUSY=D2*/ 2));
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

// 令牌/经纬度
// https://dashboard.caiyunapp.com/user/sign_in/
// 到彩云天气官方申请天气令牌后修改下面公用的令牌
// 令牌后面是你所在地的经纬度
String weatherKey = "TAkhjf8d1nlSlspN/120.26,31.55";

void initDisplay()
{
  display.init(115200);
  display.setRotation(0);
  // display.setPartialWindow(0, 0, 128, 296);
  display.setFullWindow();
  u8g2Fonts.begin(display);
  u8g2Fonts.setFontMode(1);
  u8g2Fonts.setFontDirection(0);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);

  timeClient.begin();
}

String windSpeed2WindLevel(uint16_t speed)
{
  if (speed < 1)
  {
    return "0";
  }
  else if (speed <= 5)
  {
    return "1";
  }
  else if (speed <= 11)
  {
    return "2";
  }
  else if (speed <= 19)
  {
    return "3";
  }
  else if (speed <= 28)
  {
    return "4";
  }
  else if (speed <= 38)
  {
    return "5";
  }
  else if (speed <= 49)
  {
    return "6";
  }
  else if (speed <= 61)
  {
    return "7";
  }
  else if (speed <= 74)
  {
    return "8";
  }
  else
  {
    return "9";
  }
}

/*
  英文天气变中文天气
*/
String eng2chz(String eng)
{
  if (eng == "CLEAR_DAY")
  {
    return "晴";
  }

  if (eng == "CLEAR_NIGHT")
  {
    return "晴";
  }

  if (eng == "PARTLY_CLOUDY_DAY")
  {
    return "多云";
  }

  if (eng == "PARTLY_CLOUDY_NIGHT")
  {
    return "多云";
  }

  if (eng == "CLOUDY")
  {
    return "阴";
  }

  if (eng == "LIGHT_HAZE")
  {
    return "轻度雾霾";
  }

  if (eng == "MODERATE_HAZE")
  {
    return "中度雾霾";
  }

  if (eng == "HEAVY_HAZE")
  {
    return "重度雾霾";
  }

  if (eng == "LIGHT_RAIN")
  {
    return "小雨";
  }

  if (eng == "MODERATE_RAIN")
  {
    return "中雨";
  }

  if (eng == "HEAVY_RAIN")
  {
    return "大雨";
  }

  if (eng == "STORM_RAIN")
  {
    return "暴雨";
  }

  if (eng == "FOG")
  {
    return "雾";
  }

  if (eng == "LIGHT_SNOW")
  {
    return "小雪";
  }

  if (eng == "MODERATE_SNOW")
  {
    return "中雪";
  }

  if (eng == "HEAVY_SNOW")
  {
    return "大雪";
  }

  if (eng == "STORM_SNOW")
  {
    return "暴雪";
  }

  if (eng == "DUST")
  {
    return "浮尘";
  }

  if (eng == "SAND")
  {
    return "沙尘";
  }

  if (eng == "WIND")
  {
    return "大风";
  }

  return "无";
}

/*
  画天气图标
*/
void writeIcon(String eng, int16_t line)
{
  int16_t baseHigh = 38;

  int16_t cursorX = 80;
  int16_t cursorY = line * 63 + baseHigh;

  if (eng == "CLEAR_DAY")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_100, 48, 48, GxEPD_BLACK);
  }
  if (eng == "CLEAR_NIGHT")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_100, 48, 48, GxEPD_BLACK);
  }
  if (eng == "PARTLY_CLOUDY_DAY")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_101, 48, 48, GxEPD_BLACK);
  }
  if (eng == "PARTLY_CLOUDY_NIGHT")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_101, 48, 48, GxEPD_BLACK);
  }
  if (eng == "CLOUDY")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_104, 48, 48, GxEPD_BLACK);
  }
  if (eng == "LIGHT_HAZE")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_501, 48, 48, GxEPD_BLACK);
  }
  if (eng == "MODERATE_HAZE")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_509, 48, 48, GxEPD_BLACK);
  }
  if (eng == "HEAVY_HAZE")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_514, 48, 48, GxEPD_BLACK);
  }
  if (eng == "LIGHT_RAIN")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_305, 48, 48, GxEPD_BLACK);
  }
  if (eng == "MODERATE_RAIN")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_306, 48, 48, GxEPD_BLACK);
  }
  if (eng == "HEAVY_RAIN")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_307, 48, 48, GxEPD_BLACK);
  }
  if (eng == "STORM_RAIN")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_310, 48, 48, GxEPD_BLACK);
  }
  if (eng == "FOG")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_501, 48, 48, GxEPD_BLACK);
  }
  if (eng == "LIGHT_SNOW")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_400, 48, 48, GxEPD_BLACK);
  }
  if (eng == "MODERATE_SNOW")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_401, 48, 48, GxEPD_BLACK);
  }
  if (eng == "HEAVY_SNOW")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_402, 48, 48, GxEPD_BLACK);
  }
  if (eng == "STORM_SNOW")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_403, 48, 48, GxEPD_BLACK);
  }
  if (eng == "DUST")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_503, 48, 48, GxEPD_BLACK);
  }
  if (eng == "SAND")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_503, 48, 48, GxEPD_BLACK);
  }
  if (eng == "WIND")
  {
    return display.drawBitmap(cursorX, cursorY, gImage_503, 48, 48, GxEPD_BLACK);
  }
}

void clearScreen()
{
  display.clearScreen();
}

void writeFont(int16_t cursorX, int16_t cursorY, String str, const uint8_t font[])
{
  u8g2Fonts.setFont(font);
  int16_t ta = u8g2Fonts.getFontAscent();
  int16_t td = u8g2Fonts.getFontDescent();
  int16_t th = ta - td;

  u8g2Fonts.setCursor(cursorX, cursorY + th);
  u8g2Fonts.print(str);
}

/*
  文字
*/
void writeWeatherToPaper(int16_t line, String text_day, String high,
                         String low, String text_night)
{
  int16_t baseHigh = 40;
  int16_t th = 20;
  writeFont(0, line * 63 + th * 1 + baseHigh, low + "-" + high, u8g2_font_inb19_mn);

  if (text_day == text_night)
  {
    writeFont(0, line * 63 + th * 0 + baseHigh, text_day, u8g2_font_wqy16_t_gb2312);
  }
  else
  {
    writeFont(0, line * 63 + th * 0 + baseHigh, text_day + "/" + text_night, u8g2_font_wqy14_t_gb2312);
  }
}

/*
  画矩形
*/
void writeRectToPaper(int16_t num, String high, String low)
{
  int16_t baseHigh = 270;
  display.fillRect(20 + 7 * num, baseHigh - low.toInt(), 5, -(high.toInt() - low.toInt()), GxEPD_BLACK);
}

void writeReferenceLineForRect()
{
  display.drawLine(15, 240, 17, 240, 0);
  display.drawLine(15, 255, 17, 255, 0);
  display.drawLine(15, 270, 68, 270, 0);

  writeFont(0, 235, "30", u8g2_font_fancypixels_tf);
  writeFont(0, 250, "15", u8g2_font_fancypixels_tf);
  writeFont(0, 265, " 0", u8g2_font_fancypixels_tf);
}

String caculateWeekDay(String dateStr)
{

  int y = dateStr.substring(0, 4).toInt();
  int m = dateStr.substring(5, 7).toInt();
  int d = dateStr.substring(8, 10).toInt();

  if (m == 1 || m == 2)
  {
    m += 12;
    y--;
  }
  // 使用基姆拉尔森计算公式
  int iWeek = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7;
  switch (iWeek)
  {
  case 0:
    return "一";
    break;
  case 1:
    return "二";
    break;
  case 2:
    return "三";
    break;
  case 3:
    return "四";
    break;
  case 4:
    return "五";
    break;
  case 5:
    return "六";
    break;
  case 6:
    return "日";
    break;
  }

  return "";
}

/*
  描绘天气情况
*/
void drawWeather()
{
  HTTPClient http;
  http.begin("https://api.caiyunapp.com/v2.6/" + weatherKey + "/weather?alert=false&dailysteps=7&hourlysteps=0");
  Serial.println("[HTTP] GET...\n");
  int httpCode = http.GET();
  if (httpCode != 200)
  {
    display.clearScreen();
    writeFont(0, 4, "http error...", u8g2_font_wqy16_t_gb2312);
    writeFont(0, 24, "请点击刷新按钮", u8g2_font_wqy16_t_gb2312);
    return;
  }

  String payload = http.getString();
  http.end();
  // Serial.println("payload " + payload);

  deserializeJson(JSON_CAIYUN, payload);

  JsonArray skycons = JSON_CAIYUN["result"]["daily"]["skycon_08h_20h"];
  JsonArray nightSkycons = JSON_CAIYUN["result"]["daily"]["skycon_20h_32h"];
  JsonArray temperatures = JSON_CAIYUN["result"]["daily"]["temperature"];
  String title = skycons[0]["date"];
  // Serial.println("title " + title);

  for (int i = 0; i < 3; i++)
  {
    // Serial.println("skycons value " + skycons[i]["value"].as<String>());

    writeWeatherToPaper(i, eng2chz(skycons[i]["value"].as<String>()),
                        String(temperatures[i]["max"].as<int16_t>()),
                        String(temperatures[i]["min"].as<int16_t>()),
                        eng2chz(nightSkycons[i]["value"].as<String>()));

    writeIcon(skycons[i]["value"].as<String>(), i);
  }

  // 更新时间
  // writeFont(4, 0, timeClient.getFormattedTime().substring(0, 2), u8g2_font_baby_tn);

  // 标题日期
  writeFont(20, 2, title.substring(5, 7) + " " + title.substring(8, 10), u8g2_font_freedoomr25_tn);

  // 标题星期
  String weekText = caculateWeekDay(title.substring(0, 10));
  // writeFont(112, 2, "周", u8g2_font_wqy16_t_gb2312);
  writeFont(112, 10, weekText, u8g2_font_wqy16_t_gb2312);

  // 温度参考线
  writeReferenceLineForRect();

  // 7日内温度曲线
  for (int i = 0; i < 7; i++)
  {
    writeRectToPaper(i, temperatures[i]["max"].as<String>(), temperatures[i]["min"].as<String>());
  }

  int16_t tempNow = JSON_CAIYUN["result"]["realtime"]["apparent_temperature"].as<int16_t>();
  String textNow = eng2chz(JSON_CAIYUN["result"]["realtime"]["skycon"].as<String>());
  int16_t windScale = JSON_CAIYUN["result"]["realtime"]["wind"]["speed"].as<int16_t>();
  String aqi = JSON_CAIYUN["result"]["realtime"]["air_quality"]["description"]["chn"].as<String>();

  // 天气质量
  writeFont(0, 10, aqi, u8g2_font_wqy16_t_gb2312);

  // 实时体感温度
  if (String(tempNow).length() == 1) // 调节 2 位数温度 x 轴坐标
  {
    writeFont(96, 218, String(tempNow), u8g2_font_inb19_mn);
  }
  else
  {
    writeFont(88, 218, String(tempNow), u8g2_font_inb19_mn);
  }

  // 风力
  writeFont(96, 260, windSpeed2WindLevel(windScale), u8g2_font_inb19_mn);

  // 实时天气情况
  if (textNow.length() <= 3)
  {
    // 1个字
    writeFont(96, 245, textNow, u8g2_font_wqy16_t_gb2312);
  }
  else if (textNow.length() <= 6)
  {
    // 2个字
    writeFont(88, 245, textNow, u8g2_font_wqy16_t_gb2312);
  }
  else if (textNow.length() <= 9)
  {
    // 3个字
    writeFont(80, 245, textNow, u8g2_font_wqy16_t_gb2312);
  }
  else
  {
    writeFont(80, 245, textNow, u8g2_font_wqy16_t_gb2312);
  }

  // 分钟级文字描述
  writeFont(0, 285, JSON_CAIYUN["result"]["forecast_keypoint"].as<String>(), u8g2_font_wqy12_t_gb2312);
}

void drawPapers()
{
  timeClient.update(); // 更新一下时间
  Serial.println(timeClient.getFormattedTime());
  if (timeClient.getHours() >= 22 || timeClient.getHours() <= 5)
  {
    return;
  }

  Serial.println("draw...");
  display.firstPage();
  do
  {
    drawWeather();
  } while (display.nextPage());
  display.hibernate();

  Serial.println("draw done...");
}

/*
  向屏幕上描绘 smartConfig 的信息
*/
void drawSmartConfigInfo2User()
{
  initDisplay();
  display.firstPage();
  do
  {
    writeFont(0, 4, "SmartConfig...", u8g2_font_wqy16_t_gb2312);
    writeFont(0, 24, "请使用手机打开", u8g2_font_wqy16_t_gb2312);
    writeFont(0, 44, "Esptouch 软件", u8g2_font_wqy16_t_gb2312);
    writeFont(0, 64, "设置路由信息", u8g2_font_wqy16_t_gb2312);
  } while (display.nextPage());
}

/*
  向屏幕上描绘 ip 的信息
*/
void drawWifiInfo2User(String ip)
{
  initDisplay();
  display.firstPage();
  do
  {
    writeFont(0, 4, "链接wifi成功", u8g2_font_wqy16_t_gb2312);
    writeFont(0, 24, ip, u8g2_font_wqy16_t_gb2312);
  } while (display.nextPage());
}
