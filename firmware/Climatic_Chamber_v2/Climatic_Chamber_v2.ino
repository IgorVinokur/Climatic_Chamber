#include <Arduino.h>

#include "config.h"
#include "db.h"
#include "ntp.h"
#include "hub.h"


void setup() {
  Serial.begin(115200);
  db_init();
  wifi_Init();
  bme280Init();
  encInit();
  relayInit();
  displayInit();
  ntpInit();
  hub.config(F("MyDevices"), F("Climatic Chember"), F(""));
  hub.onBuild(build);
  hub.begin();
  hub.setBufferSize(2000);
}

void loop() {

  data.tick();
  hub.tick();
  ntp.tick();
  enc.tick();
  temprelay();
  humrelay();
  AirCirculationTimer();
  VentilationTimer();
  QLampTimer();
  updateTick();
  dashboardiconStat();
 
displayMenu();

  // раз в 1 сек делаем дела
  static uint32_t ms1 = 0;
  if (millis() - ms1 >= 1000) {
    ms1 = millis();
   
    bme280Read();
    
    if (currentScreen == MAIN) {
      if (ntp.synced()) {
        clockDisplay();

      }  //Serial.println(ntp.timeString());
    }
  }


}
