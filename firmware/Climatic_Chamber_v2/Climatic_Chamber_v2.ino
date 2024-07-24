#include <Arduino.h>

#include "config.h"
#include "db.h"
#include "hub.h"
#include "wifi.h"



void setup() {
  Serial.begin(115200);

   db_init();
   wifi_Init(); 
 
  hub.onBuild(build);
  hub.begin();
  hub.setBufferSize(2000);
}


void loop() {

  hub.tick();
    


}





