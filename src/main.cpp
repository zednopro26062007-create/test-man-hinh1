#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8
#define TFT_MOSI  11
#define TFT_SCLK  12

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup()
{
    SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);

    tft.begin();

    // Thử hướng dọc trước
    tft.setRotation(0);

    // Test toàn màn hình
    tft.fillScreen(ILI9341_RED);
    delay(1000);

    tft.fillScreen(ILI9341_GREEN);
    delay(1000);

    tft.fillScreen(ILI9341_BLUE);
    delay(1000);

    // Nền đen
    tft.fillScreen(ILI9341_BLACK);

    // Chữ trắng
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(4);

    tft.setCursor(20, 130);
    tft.println("TO THICH CAU");

    tft.setCursor(30, 180);
    tft.println(",<3.<3.<3");
}

void loop()
{
    // Không cần làm gì
}