#pragma once

#include <GyverNTP.h>
GyverNTP ntp(2);

void ntpInit() {

  ntp.setGMT(mydata.gmt);  // часовой пояс. Для Москвы: 3
  ntp.setHost(mydata.ntp_srv);
  ntp.begin();
  byte count = 0;
  while (!ntp.synced()) {
    ntp.updateNow();
    delay(1000);
   if (++count > 10) break;
  }
}