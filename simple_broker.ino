#include "TinyMqtt.h"  // https://github.com/hsaturn/TinyMqtt

#define PORT 1883
MqttBroker broker(PORT);

#include <M5Stack.h>

#include "uptime.h"

/** Basic Mqtt Broker
  *
  *  +-----------------------------+
  *  | ESP                         |
  *  |       +--------+            |
  *  |       | broker |            | 1883 <--- External client/s
  *  |       +--------+            |
  *  |                             |
  *  +-----------------------------+
  *
  *  Your ESP will become a MqttBroker.
	*  You can test it with any client such as mqtt-spy for example
	*
  */

const char* ssid = "CANODECO";
const char* password = "Pendejo09";

hw_timer_t *My_timer = NULL; // Create esp32 hware timer

// void IRAM_ATTR onTimer(){
//   // digitalWrite(LED, !digitalRead(LED));
//   M5.Lcd.drawChar(random(100), 295, 5, 2);
// }

int button_state = 0;

void callbackFcn (){


}

String ipadd1;

void setup() {

  M5.begin();        // Init M5Core.  初始化 M5Core
  M5.Power.begin(); 

  M5.Lcd.setTextSize(2);
  M5.Lcd.println("BEVERIDGE INDUSTRIES");
  M5.Lcd.println("--- Rusty Halloween ---");

  Serial.begin(115200);

  if (strlen(ssid) == 0)
    M5.Lcd.println("****** PLEASE MODIFY ssid/password *************");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    // M5.Lcd.print('.');
    delay(500);
  }


  ipadd1 = WiFi.localIP().toString().c_str();
  M5.Lcd.println("Connected to: " + String(ssid));
  M5.Lcd.println("IP addr: " +  ipadd1);

  broker.begin();
  M5.Lcd.println("Broker : " + ipadd1 + ":" + String(PORT));
  M5.Lcd.println("------------------------");
  // My_timer = timerBegin(0, 80, true);
  // timerAttachInterrupt(My_timer, &onTimer, true);
  // timerAlarmWrite(My_timer, 10000, true);
  // timerAlarmEnable(My_timer); //Just Enable
    
}

void loop() {

  M5.update();  // Read the press state of the key.  读取按键 A, B, C 的状态
  broker.loop();


  // if (M5.BtnA.wasReleased() || M5.BtnA.pressedFor(1000, 200)) {
  //     M5.Lcd.print('A');
  // } else 
  if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
      M5.Lcd.print('B');
      broker.publish("/esp32_C3_kickass_lights_state","0",1);
  } else if (M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
      M5.Lcd.print('C');
      // broker.publish("/esp32_C3_kickass_lights_state","1");
  } else if (M5.BtnB.wasReleasefor(700)) {
      M5.Lcd.clear(WHITE);  // Clear the screen and set white to the
                            // background color.  清空屏幕并将白色设置为底色
      M5.Lcd.setCursor(0, 0);
  }

 // broker.publish("//llamaninos","0");


  // if (M5.BtnB.wasReleased() || M5.BtnB.pressedFor(1000, 200)) {
  //   // M5.Lcd.print("B");

      
  //   } else if(M5.BtnC.wasReleased() || M5.BtnC.pressedFor(1000, 200)) {
   
  //   M5.Lcd.print("c");

   
      
    // M5.Lcd.setCursor(5, 100);
    // M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    // M5.Lcd.print(uptime_formatter::getUptime());
    // String formatTime = formatUptime();
    //  M5.Lcd.print(formatTime);
    }


String formatUptime(){
  
  String sval;
  
  uptime::calculateUptime();

  String days = "d:" + uptime::getDays();
  String hrs = "h:" + uptime::getHours();
  String mins ="m:" + uptime::getMinutes();
  String secs ="s:" + uptime::getSeconds();
  String mill = "ms:" + uptime::getMilliseconds();

  sval = secs;

  return sval;

}
