#include "Xdisplay.h"

Xdisplay* Xdisplay::instance = nullptr;

// Private constructor
Xdisplay::Xdisplay() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

// Static method to get the singleton instance
Xdisplay& Xdisplay::getInstance() {
    if (!instance) {
        instance = new Xdisplay();
    }
    return *instance;
}

void Xdisplay::init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (true) delay(100); // More power-efficient than for(;;)
    }

    // Initial display settings
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 25);
    display.display();
}

void Xdisplay::clearDisplay() {
    display.clearDisplay();
    display.setCursor(0, 25);
}

void Xdisplay::setCursor(uint8_t x, uint8_t y) {
    display.setCursor(x, y);
}

void Xdisplay::flush() {
    display.display();
}

void Xdisplay::print(const char* str) {
    if (!str) return;  // Null check

    Serial.print(str);
    display.print(str);
}

void Xdisplay::println(const char* str) {
    if (!str) return;  // Null check

    Serial.println(str);
    display.println(str);
}

void Xdisplay::flush(const char* str) {
    if (!str) return;  // Null check

    print(str);
    flush();
}

void Xdisplay::flushln(const char* str) {
    if (!str) return;  // Null check

    println(str);
    flush();
}
