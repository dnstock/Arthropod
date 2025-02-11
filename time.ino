#include <WiFi.h>
#include "time.h"
#include "esp_sntp.h"
#include <stdarg.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#include <Wire.h>
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_WIDTH 128 // OLED display width, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char *ssid = "replace-with-your-wifi-ssid";
const char *password = "replace-with-your-wifi-password";

const char *ntpServer1 = "pool.ntp.org";
const char *ntpServer2 = "time.nist.gov";
const long gmtOffset_sec = -18000;   // UTC -5 hours
const int daylightOffset_sec = 3600; // 1 hour DST

const char *time_zone = "EST5EDT,M3.2.0,M11.1.0";  // Eastern Standard Time

void printSD(const char *str) {
  Serial.print(str);
  display.print(str);
  display.display();
}

void printSDln(const char *str) {
  Serial.println(str);
  display.clearDisplay();
  display.setCursor(0, 25);
  display.println(str);
  display.display();
}

void printSDln(struct tm *timeinfo, const char *format, ...) {
  char strftime_buf[64];
  strftime(strftime_buf, sizeof(strftime_buf), format, timeinfo);
  Serial.println(strftime_buf);
  display.clearDisplay();
  display.setCursor(0, 25);
  display.println(strftime_buf);
  display.display();
}

void printSDf(const char *format, ...) {
  char buf[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, 256, format, args);
  va_end(args);
  Serial.print(buf);
  display.print(buf);
  display.display();
}

void printSDfln(const char *format, ...) {
  char buf[256];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, 256, format, args);
  va_end(args);
  Serial.println(buf);
  display.clearDisplay();
  display.setCursor(0, 25);
  display.println(buf);
  display.display();
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    printSDln("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  display.clearDisplay();
  display.dim(false);
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.println(&timeinfo, "%A, %b %d %Y");
  display.setCursor(0, 25);
  display.setTextSize(1);
  display.println(&timeinfo, "%I:%M:%S %p");
  display.display();
}

// Callback function (gets called when time adjusts via NTP)
void timeavailable(struct timeval *t) {
  printSDln("Got time adjustment from NTP!");
  printLocalTime();
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 25);
  // First step is to configure WiFi STA and connect in order to get the current time and date.
  printSDf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  delay(2000);

  /**
   * NTP server address could be acquired via DHCP,
   *
   * NOTE: This call should be made BEFORE esp32 acquires IP address via DHCP,
   * otherwise SNTP option 42 would be rejected by default.
   * NOTE: configTime() function call if made AFTER DHCP-client run
   * will OVERRIDE acquired NTP server address
   */
  esp_sntp_servermode_dhcp(1);  // (optional)

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    printSD(".");
  }
  printSDln(" CONNECTED");

  // set notification call-back function
  sntp_set_time_sync_notification_cb(timeavailable);

  /**
   * This will set configured ntp servers and constant TimeZone/daylightOffset
   * should be OK if your time zone does not need to adjust daylightOffset twice a year,
   * in such a case time adjustment won't be handled automagically.
   */
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  /**
   * A more convenient approach to handle TimeZones with daylightOffset
   * would be to specify a environment variable with TimeZone definition including daylight adjustmnet rules.
   * A list of rules for your zone could be obtained from https://github.com/esp8266/Arduino/blob/master/cores/esp8266/TZ.h
   */
  //configTzTime(time_zone, ntpServer1, ntpServer2);
}

void loop() {
  delay(1000);
  printLocalTime();  // it will take some time to sync time :)
}
