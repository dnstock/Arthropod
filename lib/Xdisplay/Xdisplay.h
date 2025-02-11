#pragma once

#include <Adafruit_SSD1306.h>

class Xdisplay {
public:
    static Xdisplay& getInstance();

    void init();
    void clearDisplay();
    void setCursor(uint8_t x, uint8_t y);
    void print(const char* str);
    void println(const char* str);
    void flush(const char* str);
    void flushln(const char* str);
    void flush();

private:
    static Xdisplay* instance;
    static const uint8_t SCREEN_WIDTH = 128;
    static const uint8_t SCREEN_HEIGHT = 64;
    static const uint8_t SCREEN_ADDRESS = 0x3C;

    Adafruit_SSD1306 display;

    // Private constructor
    Xdisplay();

    // Prevent copy-construction
    Xdisplay(const Xdisplay&) = delete;
    Xdisplay& operator=(const Xdisplay&) = delete;
};
