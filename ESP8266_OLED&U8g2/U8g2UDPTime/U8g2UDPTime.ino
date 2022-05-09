#include <Arduino.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WifiUDP.h>
#include <String.h>
#include <NTPClient.h>
#include <Time.h>
#include <TimeLib.h>
#include <Timezone.h>


#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// Define NTP properties
#define NTP_OFFSET   60 * 60      // In seconds
#define NTP_INTERVAL 60 * 1000    // In miliseconds
#define NTP_ADDRESS  "asia.pool.ntp.org"  // change this to whatever pool is closest (see ntp.org)

// Set up the NTP UDP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

const char* ssid = "212N2F-2.4G";   // insert your own ssid 
const char* password = "M29378777";              // and password
String date;
String t;
const char * days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"} ;
const char * months[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"} ;
const char * ampm[] = {"AM", "PM"} ;

// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=12 SCL*/ D2, /* data=13 SDA*/ D1, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display

void setup(void) {
  Serial.begin(115200); // most ESP-01's use 115200 but this could vary
  timeClient.begin();   // Start the NTP UDP client
  u8g2.begin();
  u8g2.enableUTF8Print();
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
  if (WiFi.status() == WL_CONNECTED) //Check WiFi connection status
  {   
    date = "";  // clear the variables
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
    date += ", ";
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

    // Display the date and time
    Serial.println("");
    Serial.print("Local date: ");
    Serial.print(date);
    Serial.println("");
    Serial.print("Local time: ");
    Serial.print(t);

    // print the date and time on the OLED
    u8g2.clearBuffer();          // clear the internal memory
    //u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
    u8g2.setCursor(0, 16);
    u8g2.print(date);
    u8g2.setCursor(0, 32);
    u8g2.print(t);
    u8g2.sendBuffer();          // transfer internal memory to the display
  }
  else // attempt to connect to wifi again if disconnected
  {
    u8g2.clearBuffer();
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
  //delay(1000);    //Send a request to update every 10 sec (= 10,000 ms)
}
