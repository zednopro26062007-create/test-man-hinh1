#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8
#define TFT_MOSI  11
#define TFT_SCLK  12

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

bool heartVisible = true;
unsigned long lastBlink = 0;

void drawHearts()
{
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(3);

    tft.setCursor(45, 150);
    tft.print("<3 <3 <3");
}

void setup()
{
    Serial.begin(115200);

    SPI.begin(
        TFT_SCLK,
        -1,
        TFT_MOSI,
        TFT_CS
    );

    // ST7789 240x320
    tft.init(240, 320);

    // Hướng dọc
    tft.setRotation(1);

    tft.fillScreen(ST77XX_BLACK);

    // Dòng chữ
    tft.setTextColor(ST77XX_CYAN);
    tft.setTextSize(3);

    tft.setCursor(20, 80);
    tft.println("LAM NY TO NHE");

    // Tim ban đầu
    drawHearts();

    Serial.println("DONE");
}

void loop()
{
    unsigned long now = millis();

    if (now - lastBlink >= 500)
    {
        lastBlink = now;

        heartVisible = !heartVisible;

        // Xóa vùng trái tim
        tft.fillRect(
            35,
            145,
            230,
            40,
            ST77XX_BLACK
        );

        if (heartVisible)
        {
            drawHearts();
        }
    }
}