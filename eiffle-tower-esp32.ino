#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include "esp_sleep.h"

// === Wi-Fi Credentials ===
#include "secrets.h"

// === Time Zone for US Eastern Time (with DST) ===
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const char* timeZone = "EST5EDT,M3.2.0/2,M11.1.0/2";

// === Output Pin ===
#define LED_PIN 10 // GPIO10
#define WAKEUP_SECONDS_BEFORE_HOUR 20

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(LED_PIN, OUTPUT);

  // Connect Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  unsigned long wifiStart = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 5000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi failed, going to sleep");
    goToSleep();
  }

  // Configure time with timezone string (handles DST)
  configTzTime(timeZone, ntpServer1, ntpServer2);

  struct tm timeinfo;
  int retry = 0;
  while (!getLocalTime(&timeinfo) && retry < 10) {
    delay(200);
    retry++;
  }

  if (retry >= 10) {
    Serial.println("Time sync failed, going to sleep");
    goToSleep();
  }

  // Print local time (for verification)
  Serial.println(&timeinfo, "Local time: %A, %B %d %Y %H:%M:%S");

  // Calculate seconds until top of hour
  int secondsUntilTop = (60 - timeinfo.tm_min) * 60 - timeinfo.tm_sec;
  Serial.printf("Time: %02d:%02d:%02d | Seconds until top of hour: %d\n",
                timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, secondsUntilTop);

  // If we are NOT within the 20-second trigger window, go back to sleep
  if (secondsUntilTop > WAKEUP_SECONDS_BEFORE_HOUR) {
    Serial.println("Too early, sleeping again.");
    goToSleep();
  }

  // Wait for top of hour
  while (true) {
    getLocalTime(&timeinfo);
    if (timeinfo.tm_min == 0 && timeinfo.tm_sec == 0) {
      break;
    }
    delay(100);
  }

  // Activate output for 5 seconds
  Serial.println("Top of the hour! Firing output...");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);

  // Sleep until next event
  goToSleep();
}

void goToSleep() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to get time, sleeping 1 hour fallback.");
    esp_sleep_enable_timer_wakeup(3600ULL * 1000000ULL); // fallback: 1 hour
    esp_deep_sleep_start();
  }

  int currentSeconds = timeinfo.tm_min * 60 + timeinfo.tm_sec;
  int targetSeconds = 3600 - WAKEUP_SECONDS_BEFORE_HOUR;
  int sleepSeconds = targetSeconds - currentSeconds;

  if (sleepSeconds <= 0) {
    sleepSeconds += 3600;
  }

  uint64_t sleepTimeUs = (uint64_t)sleepSeconds * 1000000ULL;

  Serial.printf("Sleeping for %d seconds (%llu µs)\n", sleepSeconds, sleepTimeUs);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  esp_sleep_enable_timer_wakeup(sleepTimeUs);
  delay(100);
  esp_deep_sleep_start();
}

void loop() {
  // Not used
}
