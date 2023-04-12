#ifndef DrawPaper_H
#define DrawPaper_H

void writeIcon(String eng, int16_t line);
String eng2chz(String eng);
void initDisplay();
void clearScreen();
void writeFont(int16_t cursorX, int16_t cursorY, String str, uint8_t font[]);
void writeWeatherToPaper(int16_t line, String text_day, String high,
                         String low, String text_night);
void writeRectToPaper(int16_t num, String high, String low);
void drawWeather();
String caculateWeekDay(String dateStr);
void drawPapers();

void drawSmartConfigInfo2User();
void drawWifiInfo2User(String ip);

#endif