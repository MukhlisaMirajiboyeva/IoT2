#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "Spirealm";
const char* password = NULL;

// Create a web server on port 80
WebServer server(80);

// LED pin
const int ledPin = 2;

// Function declarations
void handleRoot();
void handleON();
void handleOFF();

void setup() {
  // Initialize serial communication at a baud rate of 115200
  Serial.begin(115200);
  delay(1000);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize Wi-Fi access point
  WiFi.softAP(ssid, password);
  Serial.println("AP created. IP address:");
  Serial.println(WiFi.softAPIP());

  // Define URL handlers
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleON);
  server.on("/off", HTTP_GET, handleOFF);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient(); 
}

// Handle the root URL ("/")
void handleRoot() {
  // HTML content to be sent to the client
  String html = "<!DOCTYPE html><html><head><title>ESP32 LED Control</title></head><body style=\"background-color:#9D81BA;\">";
  html += "<h1 style=\"text-align:center;\">ESP32 LED Control</h1>";
  html += "<div style=\"display:flex; justify-content:center;\">";
  html += "<button id=\"onBtn\" style=\"margin-right:10px; padding:10px 20px; font-size:20px; background-color:#354D73; color:white; border:none; border-radius:5px; cursor:pointer;\">ON</button>";
  html += "<button id=\"offBtn\" style=\"padding:10px 20px; font-size:20px; background-color:#660066; color:white; border:none; border-radius:5px; cursor:pointer;\">OFF</button>";
  html += "</div><script>document.getElementById('onBtn').onclick = function() { sendRequest('/on'); }; document.getElementById('offBtn').onclick = function() { sendRequest('/off'); }; function sendRequest(url) { var xhttp = new XMLHttpRequest(); xhttp.open('GET', url, true); xhttp.send(); }</script></body></html>";
  
  // Send the HTML content to the client
  server.send(200, "text/html", html); 
}

// Handle the "/on" URL
void handleON() {
  // Send a plain text response
  server.send(200, "text/plain", "ON");

  // Print to serial monitor
  Serial.println("LED ON");

  // Turn the LED on
  digitalWrite(ledPin, HIGH);
}

// Handle the "/off" URL
void handleOFF() {
  // Send a plain text response
  server.send(200, "text/plain", "OFF");

  // Print to serial monitor
  Serial.println("LED OFF");

  // Turn the LED off
  digitalWrite(ledPin, LOW); 
}
