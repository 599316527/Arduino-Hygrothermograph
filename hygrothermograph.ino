#include <SimpleDHT.h>
#include <Wire.h>
#include <math.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET    4
#define NUMFLAKES     10
#define XPOS          0
#define YPOS          1
#define DELTAY        2
#define DELAY         1

int pinDHT11 = 3;
byte temperature = 0;
byte humidity = 0;
SimpleDHT11 dht11;

Adafruit_SSD1306 display(OLED_RESET);

struct Time {
  unsigned int hour;
  unsigned char minute;
  unsigned char second;
};

Time upTime = {0, 0, 0};

void setup()   {
  Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}


void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Kyle");

  display.setCursor(40, 0);
  increaseUpTime(&upTime);
  display.print(formatUpTime(&upTime));

  display.setCursor(128 - 8, 0);
  display.print(upTime.second % 2 ? "+" : "x");

  display.setCursor(0, 16);
  if (!dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.print("temp");
    display.setTextColor(WHITE);
    display.print(" ");
    display.setTextSize(2);
    display.print((int)temperature);
    display.setTextSize(1);
    display.print("*");
    display.setTextSize(2);
    display.println("C");

    display.setCursor(0, 16 * 2 + 5);
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.print("humi");
    display.setTextColor(WHITE);
    display.print(" ");
    display.setTextSize(2);
    display.print((int)humidity);
    display.println("%");
  }
  else {
    display.setTextSize(4);
    display.print("ERROR");
  }

  display.display();

  // Delay between measurements.
  delay(DELAY * 1000);
}

String formatUpTime(Time *upTime) {
  String hh = String(upTime->hour);
  String mm = String(upTime->minute);
  String ss = String(upTime->second);

  return (upTime->hour > 9 ? hh : "0" + hh)
    + ":" + (upTime->minute > 9 ? mm : "0" + mm)
    + ":" + (upTime->second > 9 ? ss : "0" + ss);
}

void increaseUpTime(Time *upTime) {
  if (++upTime->second >= 60) {
    ++upTime->minute;
    upTime->second = 0;
  }
  if (upTime->minute >= 60) {
    ++upTime->hour;
    upTime->minute = 0;
  }
}
