#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=12*/ D2, /* data=13*/ D1, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setup(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  //u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  //u8g2.drawStr(0,0,"我好帥123");  // write something to the internal memory
  u8g2.setCursor(0, 16);
  u8g2.print("我是帥哥陳宥均"); 
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);  
}
