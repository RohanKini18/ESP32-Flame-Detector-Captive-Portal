#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

#define FLAME_SENSOR_PIN 35   // Use the DO pin of the flame sensor

const char *apSSID = "FlameDetector";
const char *apPassword = "";

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer server(80);

bool flameDetected = false;
unsigned long lastDetectionTime = 0;
int detectionCount = 0;

// If your sensor gives LOW on flame detection (most do), keep this false
bool ACTIVE_HIGH = false;

void setup() {
  Serial.begin(115200);
  pinMode(FLAME_SENSOR_PIN, INPUT);

  Serial.println("\n=== ESP32 Flame Detector Captive Portal ===");
  
  // Start Wi-Fi Access Point
  WiFi.softAP(apSSID, apPassword);
  Serial.print("Access Point Started!\nSSID: ");
  Serial.println(apSSID);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Start DNS (for captive redirection)
  dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

  // Handle any URL
  server.on("/", handleRoot);
  server.onNotFound(handleRoot);
  server.begin();

  Serial.println("Web Server started.\n");
}

void loop() {
  dnsServer.processNextRequest();
  server.handleClient();

  int sensorValue = digitalRead(FLAME_SENSOR_PIN);

  // Debug — print raw sensor value
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Detection logic
  bool detectedNow = ACTIVE_HIGH ? (sensorValue == LOW) : (sensorValue == HIGH);

  if (detectedNow) {
    if (!flameDetected || millis() - lastDetectionTime > 1000) {
      detectionCount++;
      lastDetectionTime = millis();
      flameDetected = true;
      Serial.println(" Flame Detected!");
    }
  } else {
    flameDetected = false;
  }

  delay(200);  // small delay to avoid spamming
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<title>ESP32 Flame Detector</title>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f8f9fa;color:#222;}";
  html += ".box{margin-top:50px;padding:20px;border-radius:15px;display:inline-block;background:white;box-shadow:0 0 15px rgba(0,0,0,0.2);}";
  html += "h2{color:#d63333;}";
  html += "p{font-size:1.2em;}";
  html += "</style></head><body>";
  html += "<div class='box'>";
  html += "<h2>ESP32 Flame Detection Portal </h2>";
  html += "<p>Status: <b style='color:" + String(flameDetected ? "red" : "green") + "'>";
  html += flameDetected ? "Flame Detected!" : "No Flame";
  html += "</b></p>";
  html += "<p>Flame detected <b>" + String(detectionCount) + "</b> times.</p>";
  html += "<p>(Auto-refreshes every 2 seconds)</p>";
  html += "</div></body></html>";

  server.send(200, "text/html", html);
}
