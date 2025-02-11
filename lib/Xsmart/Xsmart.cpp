#include "Xsmart.h"

Xsmart* Xsmart::instance = nullptr;

void Xsmart::begin() {
    display.init();
    display.println("[ XVision Smart ]");
    display.println("-----------------");
    display.println("   By Joeblox");
    display.flush();
    delay(3000);
}

void Xsmart::connectWiFi(const char* ssid, const char* password) {
    display.clearDisplay();
    display.print("Connecting to ");
    display.print(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        display.print(".");
    }
    display.println(" CONNECTED");
    display.flush();
}
