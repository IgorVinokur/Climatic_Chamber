#pragma once

#define GH_INCLUDE_PORTAL
#define GH_NO_FS
//#define GH_NO_HTTP_PUBLIC         // отключить доступ к файлам по http c ip/www (для esp)
//#define GH_NO_HTTP_FETCH          // отключить скачивание файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD         // отключить загрузку файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD_PORTAL  // отключить упрощённую загрузку файлов с ip/hub/upload_portal (для esp)
#include <GyverHub.h>
GyverHub hub("MyDevices", "Climatic Chember", "f017");

void build_dashboard(gh::Builder& b) {
  //    //build_common(b);
  b.Title("Dashboard");
  {
    gh::Row r(b);
     b.Label_("timedash", formattedDate).noTab(1).label("Time").size(2);
     //if (b.Button().label("value").size(1).click()) hub.update("timedash");
     
    // b.Label((ntp.dateString()).size(2).noTab(1).color(0x25b18f));
    //b.DateTime_("datet", &stamp).noTab(1).noLabel(1).size(3).color(0x25b18f);
  }
  {
    gh::Row r(b);
    b.Gauge_("Temperature").label("Temperature").noTab(1).size(2).value(temperature).range(10, 90, 5).unit("℃").color(0x25b18f);
    b.Gauge_("Humidity").label("Humidity").noTab(1).size(2).value(humidity).range(10, 90, 5).unit("%").color(0x25b18f);
    // if (b.Button().label("value").size(1).click()) hub.update("gag").value(random(100));
    // if (b.Button().label("range").click()) hub.update("gag").range(10, 90, 5);
    // if (b.Button().label("unit").click()) hub.update("gag").unit("deg");
    //if (b.Button().label("color").click()) hub.update("gag").color(rndColor());
  }
}

void build_settings(gh::Builder& b) {
  //    //build_common(b);
  bool flag_w = 0;
  bool flag_rst = 0;
  b.Title("WiFI Settings").fontSize(20);
  
  {
    gh::Row r(b);
    b.Input(mydata.staSsid).label(F("SSID")).attach(&flag_w);
    b.Pass(mydata.staPass).label(F("PASS")).attach(&flag_w);
    //b.Button(SH("wifi_save"), "Подключить");
  }
  b.Title("WiFi AP Settings").fontSize(20);
  {
    gh::Row r(b);
    b.Input(mydata.apSsid).label(F("AP SSID")).attach(&flag_w);
    b.Pass(mydata.apPass).label(F("AP PASS")).attach(&flag_w);
    //b.Button(SH("wifi_save"), "Подключить");
  }

  b.Title("NTP Settings").fontSize(20);
  {
    gh::Row r(b);
    b.Input_("host", mydata.ntp_srv).label(F("Server NTP")).size(4).attach(&flag_w);
    b.Input_("gmt", &mydata.gmt).label(F("T Zone")).size(1).attach(&flag_w);
  }

  if (flag_w) {
    data.update();
  }
{
  gh::Row r(b);
  static gh::Button btn;
  b.Button_("btn").label("Save & Reboot").noTab(0).attach(&flag_rst).fontSize(30);
}

if (flag_rst) {
  data.update();
  ESP.restart();
  }

}

void build(gh::Builder& b) {
  // if (b.build.isSet()) hlog.println(b.build.name);
  b.Menu(F("Dashboard;Configuration;Setup;Info"));

  switch (hub.menu) {
    case 0:  //Dashboard
      build_dashboard(b);
      //build_layout(b);
      break;
    case 1:  //Configuration
             //   build_passive(b);
      break;
    case 2:  //Setup
      build_settings(b);
      //   build_active2(b);
      //    build_active3(b);
      break;
    case 3:  //Info
             //    build_pairs(b);
      break;
  }
}
