#include <Arduino.h>

#include "config.h"
#include "db.h"
#include "hub.h"

void setup() {

  Serial.begin(115200);


  db_init();
  wifi_Init();

  
  ntp.setGMT(mydata.gmt);  // часовой пояс. Для Москвы: 3
  ntp.setHost(mydata.ntp_srv);
  ntp.begin();
  byte count = 0;
  while (!ntp.synced()) {
    ntp.updateNow();
    delay(1000);
   if (++count > 10) break;
  }
  

  hub.onBuild(build);
  hub.begin();
  hub.setBufferSize(2000);
}


void loop() {

  data.tick();
  hub.tick();
  ntp.tick();

if (ntp.ms() == 500) {
   formattedDate = ntp.timeString();
  }
 
}
