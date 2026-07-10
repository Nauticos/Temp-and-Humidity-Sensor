#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BUTTON_PIN 18

bool showTemperature = true;
bool lastButtonState = HIGH;

unsigned long lastDHTReadTime =0;
float currentTemp = 0.0;
float currentHum = 0.0;

void setup() {
  Serial.begin(115200);
  dht.begin();

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(20,25);
  display.print("Initialising...");
  display.display();
  delay(1000);
}

void updateDisplay() {
  display.clearDisplay();

  if (showTemperature) {
    display.setTextSize(1);
    display.setCursor(30,2);
    display.print("TEMPERATURE");
    display.drawLine(0,10,128,10,SSD1306_WHITE);
    display.setTextSize(3);
    display.setCursor(20,30);
    display.print(currentTemp, 1);
    display.print("C");
  } else {
    display.setTextSize(1);
    display.setCursor(40,2);
    display.print("HUMIDITY");
    display.drawLine(0,10,128,10,SSD1306_WHITE);
    display.setTextSize(3);
    display.setCursor(20,30);
    display.print(currentHum, 1);
    display.print("%");
  }
  display.display();
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    showTemperature = !showTemperature;
    updateDisplay();
    delay(50);
  }
  lastButtonState = buttonState;

  if (millis() - lastDHTReadTime >= 1000) {
    lastDHTReadTime = millis();

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (abs(t - currentTemp) > 0.1 || abs(h - currentHum) > 0.1) {
        currentTemp = t;
        currentHum = h;
        updateDisplay();
    }

    if (isnan(h) || isnan(t)) {
        display.setTextSize(1);
        display.setCursor(20,25);
        display.print("Sensor error!");
    }
  }
}