#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Erişim Noktası (AP) Modunu Ayarla
  String ssid = "NodeMCU-" + WiFi.macAddress();
  ssid.replace(":", "");
  WiFi.softAP(ssid.c_str());

  Serial.print("AP SSID: ");
  Serial.println(ssid);

  // LittleFS Başlat
  if (!LittleFS.begin()) {
    Serial.println("LittleFS başlatılamadı");
    return;
  }

  // HTML dosyasını sun
  server.on("/", HTTP_GET, []() {
    File file = LittleFS.open("/index.html", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });

  // 'info.html' dosyasını sun
  server.on("/info", HTTP_GET, []() {
    File file = LittleFS.open("/info.html", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });

  // 'relay.html' dosyasını sun
  server.on("/relay", HTTP_GET, []() {
    File file = LittleFS.open("/relay.html", "r");
    if (file) {
      server.streamFile(file, "text/html");
      file.close();
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });

  // CSS dosyasını sun
  server.on("/style.css", HTTP_GET, []() {
    File file = LittleFS.open("/style.css", "r");
    if (file) {
      server.streamFile(file, "text/css");
      file.close();
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });

  // JavaScript dosyasını sun
  server.on("/script.js", HTTP_GET, []() {
    File file = LittleFS.open("/script.js", "r");
    if (file) {
      server.streamFile(file, "application/javascript");
      file.close();
    } else {
      server.send(404, "text/plain", "File not found");
    }
  });

  // Web sunucusunu başlat
  server.begin();
  Serial.println("Web sunucusu başlatıldı");
}

void loop() {
  server.handleClient();
}
