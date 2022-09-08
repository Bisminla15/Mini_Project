#include "PMS.h"
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <TridentTD_LineNotify.h>
PMS pms(Serial);
PMS::DATA data;

#define SSID        "realme"   // ชื่อ Wifi
#define PASSWORD    "123456789"   // รหัส Wifi
#define LINE_TOKEN  "N5OYO2CdNNJOdZRvnaVKF29dU6XdkRgJv7VuONMOKoZ"   // TOKEN
void setup()
{
  Serial.begin(9600);
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting ",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);
  LINE.notifySticker("hello(^^)โปรดระวัง", 2, 514);
}


void loop()
{
  int x = pms.read(data);
  //Serial.println(x);
  if (x)
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();

    if (data.PM_AE_UG_1_0 >= 40)
    {
      LINE.notify("PM 1.0 : "+String(data.PM_AE_UG_1_0)+" ug/m3");
      LINE.notify("ค่าฝุ่น PM 1.0 เกินมาตราฐาน กรุณาออกจากบริเวณนี้");
    }
    Serial.println();
    if (data.PM_AE_UG_2_5 >= 60)
    {
      LINE.notify("PM 2.5 : "+String(data.PM_AE_UG_2_5)+" ug/m3");
      LINE.notify("ค่าฝุ่น PM 2.5 เกินมาตราฐาน กรุณาออกจากบริเวณนี้");
    }
    Serial.println();
    if (data.PM_AE_UG_10_0 >= 120)
    {
      LINE.notify("PM 10.0 : "+String(data.PM_AE_UG_10_0)+" ug/m3");
      LINE.notify("ค่าฝุ่น PM 10.0 เกินมาตราฐาน กรุณาออกจากบริเวณนี้");
    }
  }
}
