#include <Arduino.h>
#include "Xsmart.h"
#include "Xtime.h"

const char *ssid = "Verizon_X3PNPM";
const char *password = "calm-aid6-fund";
const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";

void setup() {
    Serial.begin(115200);
    Xsmart *xsmart = &Xsmart::getInstance();
    xsmart->begin();
    xsmart->connectWiFi(ssid, password);
    Xtime::getInstance().setupTime(ntpServer1, ntpServer2);
}

void loop() {
    Xtime::getInstance().displayTime();
    delay(1000);
}
