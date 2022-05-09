#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=12*/ D2, /* data=13*/ D1, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

int LB = D6;
int RB = D7;
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
    delay(20);
  }
  if(digitalRead(RB) == HIGH){
    count++;
    delay(20);
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
      u8g2.drawFrame(0,0,128,18);
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
      u8g2.drawFrame(0,0,128,18);
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
      u8g2.drawFrame(0,0,128,18);
    } while ( u8g2.nextPage() );
  }
}
