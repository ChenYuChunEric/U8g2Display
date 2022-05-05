/*
 * Thx for using and sharing the code
 * Hope it can help you figure uot something new
 * If so, don't forget to share with others
 * Enjoy in Arduino, Love & Peace
 * FB     : https://www.facebook.com/EricChenYuChun/
 * GitHub : https://github.com/ChenYuChunEric?tab=repositories
 * 
 * Made by Yu Chun Chen (EricChen)  2022.03
 */

#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

#define imgWidth  20
#define imgHeight 20

static const unsigned char PROGMEM logo_bmp[] =
{ 
0X00,0X0F,0X00,0XE0,0X7F,0X00,0XF0,0XFF,0X00,0XF8,0XFF,0X01,0XFC,0XF1,0X03,0XFE,
0XE0,0X07,0XFE,0XC0,0X07,0XFE,0X81,0X07,0X07,0X00,0X0F,0X03,0X00,0X0E,0X03,0X00,
0X0E,0X07,0X00,0X0F,0XFE,0X81,0X07,0XFE,0XC1,0X07,0XFE,0XE0,0X07,0XFC,0XF1,0X03,
0XF8,0XFF,0X01,0XF0,0XFF,0X00,0XE0,0X7F,0X00,0X00,0X0F,0X00,};

int LB = 25;
int RB = 26;
unsigned int count = 0;

void setup() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  pinMode(LB,INPUT);
  pinMode(RB,INPUT);
}

void loop() {
  if(digitalRead(LB) == HIGH){
    count--;
    delay(100);
  }
  if(digitalRead(RB) == HIGH){
    count++;
    delay(100);
  }
  
  if(count%3 == 0){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_luBS18_tf); //設定字型
    u8g2.firstPage();
    do {
      u8g2.setCursor(44, 18);
      u8g2.print("Item 1");
      u8g2.setCursor(44, 41);
      u8g2.print("Item 2");
      u8g2.setCursor(44, 64);
      u8g2.print("Item 3");
      u8g2.drawXBMP(10, 0, imgWidth, imgHeight, logo_bmp);
    } while ( u8g2.nextPage() );
  }
  if(count%3 == 1){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_luBS18_tf); //設定字型
    u8g2.firstPage();
    do {
      u8g2.setCursor(44, 64);
      u8g2.print("Item 1");
      u8g2.setCursor(44, 18);
      u8g2.print("Item 2");
      u8g2.setCursor(44, 41);
      u8g2.print("Item 3");
      u8g2.drawXBMP(10, 0, imgWidth, imgHeight, logo_bmp);
    } while ( u8g2.nextPage() );
  }
  if(count%3 == 2){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_luBS18_tf); //設定字型
    u8g2.firstPage();
    do {
      u8g2.setCursor(44, 41);
      u8g2.print("Item 1");
      u8g2.setCursor(44, 64);
      u8g2.print("Item 2");
      u8g2.setCursor(44, 18);
      u8g2.print("Item 3");
      u8g2.drawXBMP(10, 0, imgWidth, imgHeight, logo_bmp);
    } while ( u8g2.nextPage() );
  }
}
