#include <Arduino.h>
#include <U8g2lib.h>
#include "DHT.h"
#define DHTPIN D5     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=12*/ D2, /* data=13*/ D1, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setup(void) {
  dht.begin();
  u8g2.begin();
  u8g2.enableUTF8Print();
  Serial.begin(115200);
}

void loop(void) {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(t);
  Serial.println(h);
  delay(1000);

  String OutputH = String("H:") + h + "%";
  String OutputT = String("T:") + t + (char)223 +"C";
  
  u8g2.clearBuffer();          // clear the internal memory
  //u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  //u8g2.drawStr(0,16,"我好帥123");  // write something to the internal memory
  u8g2.setCursor(0, 16);
  u8g2.print(OutputH);
  u8g2.setCursor(0, 32);
  u8g2.print(OutputT);
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}
