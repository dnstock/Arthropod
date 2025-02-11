#include <Wire.h>
#include <WiFi.h>
#include "Xdisplay.h"

class Xsmart {
public:
    static Xsmart& getInstance() {
        static Xsmart instance;
        return instance;
    }

    void begin();
    void connectWiFi(const char* ssid, const char* password);

private:
    Xsmart() {}  // Private constructor
    Xsmart(const Xsmart&) = delete;  // Prevent copy-construction
    Xsmart& operator=(const Xsmart&) = delete;  // Prevent assignment

    static Xsmart* instance;
    Xdisplay& display = Xdisplay::getInstance();  // Singleton instance
};
