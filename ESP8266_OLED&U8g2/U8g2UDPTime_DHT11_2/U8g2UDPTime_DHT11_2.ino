/*
   Thx for using and sharing the code
   Hope it can help you figure uot something new
   If so, don't forget to share with others
   Enjoy in Arduino, Love & Peace
   FB     : https://www.facebook.com/EricChenYuChun/
   GitHub : https://github.com/ChenYuChunEric?tab=repositories

   Made by Yu Chun Chen (EricChen)  2022.03
*/
#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WifiUDP.h>
#include <String.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>
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

//定義NTP間隔
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "asia.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

//設定NTP UDP用戶端
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

//wifi帳號密碼
const char* ssid = "";
const char* password = "";

//定義時間變數
String date;
String t;
const char * days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"} ;
const char * months[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"} ;
const char * ampm[] = {"AM", "PM"} ;

//設定SSD1306使用U8g2腳位 The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=12 SCL*/ D2, /* data=13 SDA*/ D1, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setup(void) {
  Serial.begin(115200); // most ESP-01's use 115200 but this could vary
  timeClient.begin();   // Start the NTP UDP client
  dht.begin();
  u8g2.begin();
  u8g2.enableUTF8Print();
  //u8g2.setDisplayRotation(U8G2_R2);  //U8G2_R0 不旋轉
                                       //U8G2_R1 旋轉90度
                                       //U8G2_R2 旋轉180度
                                       //U8G2_R3 旋轉270度
                                       //U8G2_MIRROR 不旋轉，但影像是水平鏡像呈現
  u8g2.setFont(u8g2_font_ncenB08_tr);
  // Connect to wifi
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.print(ssid);
  u8g2.clearBuffer();
  u8g2.drawStr(0,16,"Connecting to WiFi...");
  u8g2.sendBuffer();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi at ");
  Serial.print(WiFi.localIP());
  Serial.println("");
  u8g2.drawStr(0, 32, "Connected.");
  u8g2.setCursor(0, 48);
  u8g2.print("IP:");
  u8g2.print(WiFi.localIP()); 
  u8g2.sendBuffer();
  delay(1000);
}

void loop(void) {
  if (WiFi.status() == WL_CONNECTED){
    //WiFi時鐘   
    date = "";
    t = "";
    // update the NTP client and get the UNIX UTC timestamp 
    timeClient.update();
    unsigned long epochTime =  timeClient.getEpochTime();
    // convert received time stamp to time_t object
    time_t local, utc;
    utc = epochTime;
    // Then convert the UTC UNIX timestamp to local time
    TimeChangeRule TaipeiEDT = {"EDT", Second, Sun, Mar, 2, +420};  //UTC - 5 hours - change this as needed
    TimeChangeRule TaipeiEST = {"EST", First, Sun, Nov, 2, +420};   //UTC - 6 hours - change this as needed
    Timezone TaipeiAsia(TaipeiEDT, TaipeiEST);
    local = TaipeiAsia.toLocal(utc);
    // now format the Time variables into strings with proper names for month, day etc
    date += year(local);
    date += "/";
    date += months[month(local)-1];
    date += "/";
    if(day(local) < 10)  // add a zero if day is under 10
      date += "0";
    date += day(local);
    date += ",";
    date += days[weekday(local)-1];
    // format the time to 12-hour format with AM/PM
    if(hourFormat12(local) < 10)  // add a zero if hour is under 10
      t += "0";
    t += hourFormat12(local);
    t += ":";
    if(minute(local) < 10)  // add a zero if minute is under 10
      t += "0";
    t += minute(local);
    t += ":";
    if(second(local) < 10)  // add a zero if second is under 10
      t += "0";
    t += second(local);
    t += " ";
    t += ampm[isPM(local)];

    //濕度與溫度
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();
    String OutputH = String(humi) + "%";
    String OutputT = String(temp) +"°C";

    //檢查時間
    Serial.println();
    Serial.print("Local date: ");
    Serial.print(date);
    Serial.println();
    Serial.print("Local time: ");
    Serial.print(t);
    //顯示時間
    u8g2.clearBuffer();        
    u8g2.setFont(u8g2_font_t0_17b_tf); // choose a suitable font
    u8g2.setCursor(0, 11);
    u8g2.print(date);
    u8g2.setFont(u8g2_font_luBS18_tf ); // choose a suitable font
    u8g2.setCursor(0, 40);
    u8g2.print(t);
    //顯示溫溼度
    u8g2.setFont(u8g2_font_t0_17b_tf); // choose a suitable font
    u8g2.setCursor(0, 64);
    u8g2.print(OutputT);
    u8g2.print(" ");
    u8g2.print(OutputH);
    u8g2.sendBuffer();
  }
  else{
    u8g2.clearBuffer();
    u8g2.drawStr(0,16,"Connecting to WiFi...");
    u8g2.sendBuffer();
    WiFi.begin(ssid, password);
    u8g2.drawStr(0, 32, "Connected.");
    u8g2.setCursor(0, 48);
    u8g2.print("IP:");
    u8g2.print(WiFi.localIP()); 
    u8g2.sendBuffer();
    delay(1000);
  }
}
