#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// =========================
// CẤU HÌNH CHÂN TFT
// =========================
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8
#define TFT_MOSI 11
#define TFT_SCLK 12

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// =========================
// BIẾN THỜI GIAN & TRẠNG THÁI (STATE MACHINE)
// =========================
unsigned long animationStart = 0; // Thời điểm bắt đầu kịch bản
unsigned long lastBlink = 0;      // Bộ đếm cho hiệu ứng nháy
int currentPhase = -1;            // Theo dõi đang ở Phase nào
bool toggleState = true;          // Trạng thái Bật/Tắt của hiệu ứng

void setup() {
    Serial.begin(115200);
    delay(500);

    // Khởi tạo màn hình
    SPI.begin(TFT_SCLK, -1, TFT_MOSI, TFT_CS);
    tft.init(240, 320);
    tft.setRotation(1); // Xoay ngang (320x240)
    tft.fillScreen(ST77XX_BLACK);

    animationStart = millis(); // Bấm đồng hồ tính giờ!
    Serial.println("🚀 Bat dau kich ban to tinh 20s!");
}

void loop() {
    unsigned long now = millis();
    unsigned long elapsed = now - animationStart; // Thời gian đã trôi qua

    int newPhase = 0;

    // --- BỘ ĐỊNH TUYẾN THỜI GIAN (Timeline) ---
    if (elapsed < 6000) {
        newPhase = 0; // Từ 0 -> 6 giây
    } 
    else if (elapsed < 12000) {
        newPhase = 1; // Từ 6 -> 12 giây
    } 
    else if (elapsed < 20000) {
        newPhase = 2; // Từ 12 -> 20 giây
    } 
    else {
        // Quá 20s -> Reset lại kịch bản từ đầu!
        animationStart = now; 
        newPhase = 0;
    }

    // --- NẾU CHUYỂN SANG GIAI ĐOẠN MỚI -> XÓA MÀN HÌNH 1 LẦN ---
    if (newPhase != currentPhase) {
        currentPhase = newPhase;
        tft.fillScreen(ST77XX_BLACK);
        
        // Vẽ lại các thành phần tĩnh của từng Phase để không bị nháy màn
        if (currentPhase == 0) {
            tft.setTextColor(ST77XX_CYAN);
            tft.setTextSize(3);
            tft.setCursor(50, 60);  tft.println("To Thich Cau");
            tft.setCursor(30, 110); tft.println("Lam ny to nhe");
        }
    }

    // ==========================================
    // XỬ LÝ HIỆU ỨNG CHO TỪNG GIAI ĐOẠN
    // ==========================================
    
    // PHASE 0: Nháy trái tim (Mỗi 500ms)
    if (currentPhase == 0) {
        if (now - lastBlink >= 500) {
            lastBlink = now;
            toggleState = !toggleState;

            tft.fillRect(45, 175, 230, 40, ST77XX_BLACK); // Xóa tim cũ
            if (toggleState) {
                tft.setTextColor(ST77XX_RED);
                tft.setTextSize(3);
                tft.setCursor(60, 180);
                tft.print("<3 <3 <3");
            }
        }
    }
    
    // PHASE 1: Ép cung - Chữ nháy liên tục 2 màu Đỏ / Vàng (Mỗi 300ms)
    else if (currentPhase == 1) {
        if (now - lastBlink >= 300) {
            lastBlink = now;
            toggleState = !toggleState;

            tft.setTextSize(4);
            tft.setCursor(30, 100);
            
            if (toggleState) {
                tft.setTextColor(ST77XX_RED);
            } else {
                tft.setTextColor(ST77XX_YELLOW);
            }
            tft.print("DONG Y NHA?");
            
            tft.setCursor(120, 160);
            tft.print(":3");
        }
    }

    // PHASE 2: Bùng nổ pháo hoa + "I <3 U" siêu to (Mỗi 100ms)
    else if (currentPhase == 2) {
        if (now - lastBlink >= 100) {
            lastBlink = now;
            
            // Vẽ 1 hình tròn màu ngẫu nhiên (Pháo hoa)
            int r = random(5, 30);
            int x = random(r, 320 - r);
            int y = random(r, 240 - r);
            uint16_t randomColor = random(0x0000, 0xFFFF);
            tft.fillCircle(x, y, r, randomColor);

            // Ghi đè chữ I <3 U lên trên cùng để không bị pháo hoa che lấp
            tft.setTextSize(5);
            tft.setCursor(60, 100);
            tft.setTextColor(ST77XX_WHITE); tft.print("I ");
            tft.setTextColor(ST77XX_RED);   tft.print("<3 ");
            tft.setTextColor(ST77XX_WHITE); tft.print("U");
        }
    }
}