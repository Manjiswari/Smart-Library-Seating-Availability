#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SEAT1 13
#define SEAT2 12
#define SEAT3 14

bool seat1Occupied = false;
bool seat2Occupied = false;
bool seat3Occupied = false;

bool lastSeat1 = false;
bool lastSeat2 = false;
bool lastSeat3 = false;

int totalSeats = 3;
int availableSeats = 3;

unsigned long previousMillis = 0;
const long interval = 500;

void updateSeats();
void updateLCD();
void connectWiFi();
void handleRoot();
void handleSeatData();
void notFound();
void connectWiFi() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");

  delay(1500);
}

void setup() {

  Serial.begin(115200);

  pinMode(SEAT1, INPUT_PULLUP);
  pinMode(SEAT2, INPUT_PULLUP);
  pinMode(SEAT3, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Library");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  delay(2000);

  connectWiFi();

  server.on("/", handleRoot);

  server.on("/api/seats", HTTP_GET, handleSeatData);

  server.onNotFound(notFound);

  server.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Server Started");

  delay(1000);

  updateSeats();
  updateLCD();
}
void loop() {

  server.handleClient();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    updateSeats();
    updateLCD();
  }
}

void updateSeats() {

  seat1Occupied = digitalRead(SEAT1) == LOW;
  seat2Occupied = digitalRead(SEAT2) == LOW;
  seat3Occupied = digitalRead(SEAT3) == LOW;

  availableSeats = totalSeats;

  if (seat1Occupied)
    availableSeats--;

  if (seat2Occupied)
    availableSeats--;

  if (seat3Occupied)
    availableSeats--;

  if (seat1Occupied != lastSeat1 ||
      seat2Occupied != lastSeat2 ||
      seat3Occupied != lastSeat3) {

    Serial.println("---------------");
    Serial.print("Seat 1 : ");
    Serial.println(seat1Occupied ? "Occupied" : "Available");

    Serial.print("Seat 2 : ");
    Serial.println(seat2Occupied ? "Occupied" : "Available");

    Serial.print("Seat 3 : ");
    Serial.println(seat3Occupied ? "Occupied" : "Available");

    Serial.print("Available Seats : ");
    Serial.println(availableSeats);

    lastSeat1 = seat1Occupied;
    lastSeat2 = seat2Occupied;
    lastSeat3 = seat3Occupied;
  }
}
void updateLCD() {

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Available:");

  lcd.setCursor(11, 0);
  lcd.print(availableSeats);

  lcd.setCursor(0, 1);

  if (availableSeats == totalSeats) {

    lcd.print("All Seats Free");

  }
  else if (availableSeats == 0) {

    lcd.print("Library Full");

  }
  else {

    lcd.print("Occupied: ");
    lcd.print(totalSeats - availableSeats);

  }
}

void handleRoot() {

  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>Smart Library</title>";
  html += "<script>";
  html += "window.location='/index.html';";
  html += "</script>";
  html += "</head>";
  html += "<body>";
  html += "Loading...";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void handleSeatData() {

  String json = "{";

  json += "\"total\":";
  json += totalSeats;
  json += ",";

  json += "\"available\":";
  json += availableSeats;
  json += ",";

  json += "\"occupied\":";
  json += (totalSeats - availableSeats);
  json += ",";

  json += "\"seat1\":";
  json += seat1Occupied ? "true" : "false";
  json += ",";

  json += "\"seat2\":";
  json += seat2Occupied ? "true" : "false";
  json += ",";

  json += "\"seat3\":";
  json += seat3Occupied ? "true" : "false";

  json += "}";

  server.send(200, "application/json", json);
}

void notFound() {

  server.send(404, "text/plain", "404 - Page Not Found");

}
