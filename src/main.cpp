#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Spirealm";
const char* password = NULL;
WebServer server(80);
const int ledPin = 2;

void handleRoot();
void handleON();
void handleOFF();

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(ledPin, OUTPUT);
  WiFi.softAP(ssid, password);
  Serial.println("AP created. IP address:");
  Serial.println(WiFi.softAPIP());
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleON);
  server.on("/off", HTTP_GET, handleOFF);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); 
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP32 LED Control</title></head><body style=\"background-color:#9D81BA;\">";
  html += "<h1 style=\"text-align:center;\">ESP32 LED Control</h1>";
  html += "<div style=\"display:flex; justify-content:center;\">";
  html += "<button id=\"onBtn\" style=\"margin-right:10px; padding:10px 20px; font-size:20px; background-color:#354D73; color:white; border:none; border-radius:5px; cursor:pointer;\">ON</button>";
  html += "<button id=\"offBtn\" style=\"padding:10px 20px; font-size:20px; background-color:#660066; color:white; border:none; border-radius:5px; cursor:pointer;\">OFF</button>";
  html += "</div><script>document.getElementById('onBtn').onclick = function() { sendRequest('/on'); }; document.getElementById('offBtn').onclick = function() { sendRequest('/off'); }; function sendRequest(url) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', url, true); xhttp.send(); }</script></body></html>";
  server.send(200, "text/html", html); 
}

void handleON() {
  server.send(200, "text/plain", "ON");
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH);
}

void handleOFF() {
  server.send(200, "text/plain", "OFF");
  Serial.println("LED OFF");
  digitalWrite(ledPin, LOW); 
}
