#include <ESP8266WiFi.h> //
#include <ESP8266WebServer.h>


const char* ssid = "WiFiSSID";        //  Wi-Fi network name (SSID)
const char* password = "WiFiPassword"; //  Wi-Fi password

const int ledPin = D2; // Connect an LED to pin D2

// Create a web server instance on port 80
ESP8266WebServer server(80);

void setup() {
  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Connect to Wi-Fi using the provided credentials
  WiFi.begin(ssid, password);
  
  // Wait until Wi-Fi is connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();
}

void handleRoot() {
  // HTML response to display a basic web page
  String html = "<html><body>";
  html += "<h1>Smart Lighting Control</h1>";
  html += "<p><a href='/on'>Turn On</a></p>";
  html += "<p><a href='/off'>Turn Off</a></p>";
  html += "</body></html>";
  
  // Send the HTML response with a 200 OK status
  server.send(200, "text/html", html);
}

void handleOn() {
  // Turn the LED on
  digitalWrite(ledPin, HIGH);
  
  // Respond with a text message
  server.send(200, "text/plain", "Light is on");
}

void handleOff() {
  // Turn the LED off
  digitalWrite(ledPin, LOW);
  
  // Respond with a text message
  server.send(200, "text/plain", "Light is off");
}
