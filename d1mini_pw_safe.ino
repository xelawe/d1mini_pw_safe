
/*
   Blink and OTA
   Turns on the onboard LED on for one second, then off for one second, repeatedly.
   This uses delay() to pause between LED toggles.
*/
#define serdebug
#ifdef serdebug
#define DebugPrint(...) {  Serial.print(__VA_ARGS__); }
#define DebugPrintln(...) {  Serial.println(__VA_ARGS__); }
#else
#define DebugPrint(...) { }
#define DebugPrintln(...) { }
#endif

#include "config_tool.h"
#include "tools_wifi.h"
#include "ota_tool.h"
#include "mqtt_tool.h"
#include "epaper_tool.h"



void callback_mqtt(char* topic, byte* payload, unsigned int length) {

}

void setup() {
#ifdef serdebug
  Serial.begin(115200);
#endif

  DebugPrintln("\n" + String(__DATE__) + ", " + String(__TIME__) + " " + String(__FILE__));

  init_epaper();

  init_config();

  if ( conf_void == true ) {
    mark_epaper( );
  }

  wifi_init("D1miniPWSafe");
  delay(500);

  init_ota("D1miniPWSafe");

  //  pinMode(BUILTIN_LED, OUTPUT);  // initialize onboard LED as output

  init_mqtt(callback_mqtt);

}

void loop() {

  check_ota();

  //  digitalWrite(BUILTIN_LED, HIGH);  // turn on LED with voltage HIGH
  delay(1000);                      // wait one second
  //  digitalWrite(BUILTIN_LED, LOW);   // turn off LED with voltage LOW
  //  delay(1000);                      // wait one second
}
