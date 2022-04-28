/*
  ************第一段************
  #include <Arduino.h>
  #include <U8g2lib.h>

  U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

  int LB = 36;            //Left Button
  int RB = 39;            //Right Button

  Serial.begin(115200);
  u8g2.begin();
  pinMode(LB, INPUT);
  pinMode(RB, INPUT);

  u8g2.clearBuffer();                   // 清除

  u8g2.setFont(u8g2_font_t0_13b_tf);    // 設定字型
  u8g2.setCursor(XStart, YStart);       // 設定起始位置
  u8g2.print(“Text”);                   // 顯示

  u8g2.sendBuffer();                    // 輸出

  //計算字寬、字高
  int a = u8g2.getAscent();          // 取得當前字型的字高(預設是基準線之上)
  int b = u8g2.getDescent();         // 取得當前字型的字深(預設是基準線之下)
  int c = u8g2.getStrWidth("Thing1");// 取得字串 "Thing1" 寬度
  Serial.print("Ascent:  ");
  Serial.print(a);
  Serial.print("   Descent:  ");
  Serial.print(b);
  Serial.print("   StrWidth:  ");
  Serial.println(c);
  ************第一段************

  ************第二段************
  u8g2.drawFrame(XStart, YStart, XWidth, YHeight);
  ************第二段************

  ************第三段************
  Int x;
  //偵測按鈕按下並使用變數 x 儲存次數
  If (digitalRead(LB) == HIGH) {
    x -= 1;
    delay(200);
  }
  if (digitalRead(RB) == HIGH) {
    x += 1;
    delay(200);
  }
  //讓 x 值在0~3之間轉換 (看是要循環選單或是需要返回)
  if (x < 0) {
    x = 0;
    //x = 3;
  }
  if (x > 3) {
    x = 3;
    //x = 0;
  }
  ************第三段************

  ************第四段************
  u8g2.drawRFrame(XStart, YStart, XWidth, YHeight, Radius);
  ************第四段************

  ************第五段************
  u8g2.setFontMode(1);        // Transparent
  u8g2.setDrawColor(1);       // Light
  u8g2.setDrawColor(2);       // Light ←→ Dark

  u8g2.drawBox(XStart, YStart, XWidth, YHeight);    //實心長方形
  ************第五段************

  ************第六段************
  int count = 0;
  //偵測按鈕按下並使用變數 x 儲存次數  count紀錄選項並判斷換頁
  if (digitalRead(LB) == HIGH) {
    x -= 1;
    count -= 1;
    delay(200);
  }
  if (digitalRead(RB) == HIGH) {
    x += 1;
    count += 1;
    delay(200);
  }
  //讓 count 值在0~7之間轉換
  if (count < 0) {
    count = 7;
  }
  if (count > 7) {
    count = 0;
  }
  ************第六段************
*/
