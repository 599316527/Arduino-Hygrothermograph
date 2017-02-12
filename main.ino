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

unsigned int uptime = 0;

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
  display.print(getUpTime(++uptime * DELAY));

  display.setCursor(128 - 8, 0);
  display.print(uptime % 2 ? "+" : "x");

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

String getUpTime(int sec) {
  int h = sec / 3600;
  sec -= h * 3600;
  int m = sec / 60;
  sec -= m * 60;
  
  String hh = String(h);
  String mm = String(m);
  String ss = String(sec);
  
  return (h > 9 ? hh : "0" + hh) + ":" + (m > 9 ? mm : "0" + mm) + ":" + (sec > 9 ? ss : "0" + ss);
}

