#include <TFT_eSPI.h>
#include <WiFi.h>

TFT_eSPI tft = TFT_eSPI();

const char* ssid = "YOUR_NETWORK_SSID";
const char* password = "YOUR_PASSWORD";

const int bootPin = 0;
int currentItem = 0;
int selectedItem = -1;
String ipAddress = "";
String signalStrength = "";
String macAddress = "";

unsigned long pressStartTime = 0;
bool buttonPressed = false;
const unsigned long HOLD_TIME = 600;

void connectWiFi() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(10, 50);
  tft.print("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  
  ipAddress = WiFi.localIP().toString();
  signalStrength = String(WiFi.RSSI()) + " dBm";
  macAddress = WiFi.macAddress();
}

void showMenu() {
  selectedItem = -1;
  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(5, 3);               // ← левее и выше
  tft.print("WiFi MONITOR");
  
  tft.setTextSize(1);
  const char* items[] = {"SSID", "PASSWORD", "IP ADDRESS", "MAC ADDRESS", "SIGNAL"};
  
  for (int i = 0; i < 5; i++) {
    if (i == currentItem) {
      tft.setTextColor(TFT_YELLOW);
    } else {
      tft.setTextColor(TFT_WHITE);
    }
    tft.setCursor(30, 30 + i * 18);  // ← пункты выше
    tft.print(items[i]);
  }
  
  tft.setTextColor(TFT_RED);
  tft.setCursor(10, 130);
  tft.print("Short: scroll");
  tft.setCursor(10, 143);
  tft.print("Hold: select");
}

void showSelected() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(2);
  tft.setCursor(10, 15);
  
  switch(selectedItem) {
    case 0:
      tft.println("SSID:");
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(1);
      tft.setCursor(10, 55);
      tft.println(ssid);
      break;
    case 1:
      tft.println("PASSWORD:");
      tft.setTextColor(TFT_YELLOW);
      tft.setTextSize(1);
      tft.setCursor(10, 55);
      tft.println(password);
      break;
    case 2:
      tft.println("IP ADDRESS:");
      tft.setTextColor(TFT_GREEN);
      tft.setTextSize(1);
      tft.setCursor(10, 55);
      tft.println(ipAddress);
      break;
    case 3:
      tft.println("MAC ADDRESS:");
      tft.setTextColor(TFT_GREEN);
      tft.setTextSize(1);
      tft.setCursor(10, 55);
      tft.println(macAddress);
      break;
    case 4:
      tft.println("SIGNAL:");
      tft.setTextColor(TFT_GREEN);
      tft.setTextSize(1);
      tft.setCursor(10, 55);
      tft.println(signalStrength);
      tft.setCursor(10, 75);
      tft.print("Quality: ");
      int rssi = WiFi.RSSI();
      int quality;
      if (rssi <= -100) quality = 0;
      else if (rssi >= -50) quality = 100;
      else quality = 2 * (rssi + 100);
      tft.print(quality);
      tft.println("%");
      break;
  }
  
  tft.setTextColor(TFT_RED);
  tft.setTextSize(1);
  tft.setCursor(10, 120);
  tft.print("Hold to return");
}

void checkButton() {
  int buttonState = digitalRead(bootPin);
  
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;
    pressStartTime = millis();
  }
  
  if (buttonState == HIGH && buttonPressed) {
    unsigned long pressDuration = millis() - pressStartTime;
    
    if (pressDuration < HOLD_TIME) {
      if (selectedItem == -1) {
        currentItem++;
        if (currentItem > 4) currentItem = 0;
        showMenu();
      } else {
        selectedItem = -1;
        showMenu();
      }
    } else {
      if (selectedItem == -1) {
        selectedItem = currentItem;
        showSelected();
      } else {
        selectedItem = -1;
        showMenu();
      }
    }
    buttonPressed = false;
  }
}

void showSplash() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextSize(3);
  tft.setCursor(20, 35);
  tft.println("WiFi");
  tft.setCursor(15, 70);
  tft.println("MONITOR");
  
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextSize(1);
  tft.setCursor(35, 110);
  tft.println("by ESPDAN");
  
  delay(2000);
}

void setup() {
  pinMode(bootPin, INPUT_PULLUP);
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);
  
  tft.init();
  tft.setRotation(1);
  
  showSplash();
  connectWiFi();
  showMenu();
}

void loop() {
  checkButton();
  delay(10);
}