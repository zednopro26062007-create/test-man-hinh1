#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// ========================================
// TFT PINS
// ========================================
#define TFT_CS    10
#define TFT_DC     9
#define TFT_RST    8

#define TFT_MOSI  11
#define TFT_SCLK  12

// ========================================
// TFT OBJECT
// ========================================
Adafruit_ST7789 tft(
    TFT_CS,
    TFT_DC,
    TFT_RST
);

// ========================================
// SETUP
// ========================================
void setup()
{
    Serial.begin(115200);
    delay(500);

    // SPI
    SPI.begin(
        TFT_SCLK,
        -1,         // MISO không dùng
        TFT_MOSI,
        TFT_CS
    );

    // ST7789 240x320
    tft.init(240, 320);

    // ====================================
    // ROTATION 1 = NGANG 320x240
    // ====================================
    tft.setRotation(1);

    // ====================================
    // BACKGROUND
    // ====================================
    tft.fillScreen(ST77XX_BLACK);

    // ====================================
    // TITLE
    // ====================================
    tft.setTextSize(3);
    tft.setTextColor(ST77XX_CYAN);

    tft.setCursor(20, 30);
    tft.println("ASTRAFOX");

    // ====================================
    // STATUS
    // ====================================
    tft.setTextSize(2);
    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(20, 90);
    tft.println("TFT: ST7789");

    tft.setCursor(20, 120);
    tft.println("RES: 320x240");

    tft.setCursor(20, 150);
    tft.println("SPI: OK");

    tft.setCursor(20, 190);
    tft.setTextColor(ST77XX_GREEN);
    tft.println("SYSTEM READY");

    Serial.println("================================");
    Serial.println("ASTRAFOX TFT");
    Serial.println("ST7789 240x320");
    Serial.println("Rotation: 1");
    Serial.println("Display: 320x240");
    Serial.println("SYSTEM READY");
    Serial.println("================================");
}

void loop()
{
}