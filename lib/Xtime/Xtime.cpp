#include "Xtime.h"
#include "time.h"
#include "esp_sntp.h"

Xtime* Xtime::instance = nullptr;

void Xtime::setupTime(const char* ntpServer1, const char* ntpServer2) {
    if(ntpServer1 && ntpServer2) {
        esp_sntp_servermode_dhcp(1);
        sntp_set_time_sync_notification_cb(timeSyncCallback);
        configTime(-18000, 3600, ntpServer1, ntpServer2);
    }
}

void Xtime::displayTime() {
    display.clearDisplay();

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        display.flushln("No time available (yet)");
        return;
    }

    char dateStr[32];
    char timeStr[32];
    strftime(dateStr, sizeof(dateStr), "%A, %b %d %Y", &timeinfo);
    strftime(timeStr, sizeof(timeStr), "%I:%M:%S %p", &timeinfo);

    display.setCursor(0, 20);
    display.println(dateStr);

    display.setCursor(0, 35);
    display.println(timeStr);

    display.flush();
}

void Xtime::timeSyncCallback(struct timeval *t) {
    if (instance) {
        instance->display.flushln("Got time adjustment from NTP!");
        instance->displayTime();
    }
}
