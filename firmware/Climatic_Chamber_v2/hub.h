#pragma once
#define GH_INCLUDE_PORTAL
//#define GH_NO_HTTP_PUBLIC         // отключить доступ к файлам по http c ip/www (для esp)
//#define GH_NO_HTTP_FETCH          // отключить скачивание файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD         // отключить загрузку файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD_PORTAL  // отключить упрощённую загрузку файлов с ip/hub/upload_portal (для esp) 



#include <GyverHub.h>

GyverHub hub("MyDevices", "Climatic Chember", "");



void build_dashboard(gh::Builder& b) {
//    //build_common(b);
    b.Title("Dashboard");
    {
    gh::Row r(b);
        static uint32_t stamp;
        b.DateTime_("datet", &stamp).noTab(1).noLabel(1).size(3).color(0x25b18f);
        
    }
    {
      gh::Row r(b);
        b.Gauge_("Temperature").label("Temperature").noTab(1).size(2).value(34).range(10, 90, 5).unit("℃").color(0x25b18f);
        b.Gauge_("Humidity").label("Humidity").noTab(1).size(2).value(85).range(10, 90, 5).unit("%").color(0x25b18f);
       // if (b.Button().label("value").size(1).click()) hub.update("gag").value(random(100));
       // if (b.Button().label("range").click()) hub.update("gag").range(10, 90, 5);
       // if (b.Button().label("unit").click()) hub.update("gag").unit("deg");
        //if (b.Button().label("color").click()) hub.update("gag").color(rndColor());

    }
    
}

void build_settings(gh::Builder& b) {
//    //build_common(b);
    bool flag_w = 0;
    b.Title("Settings");
    {
    gh::Row r(b);
     b.Input(db[dbid::staSsid].toText()).label(F("SSID")).attach(&flag_w);
     //b.Pass(dbid::staPass, "Pass");
      //b.Button(SH("wifi_save"), "Подключить");
    }
}

void build(gh::Builder& b) {
   // if (b.build.isSet()) hlog.println(b.build.name);
    b.Menu(F("Dashboard;Configuration;Setup;Info"));

    switch (hub.menu) {
        case 0: //Dashboard
            build_dashboard(b);
            //build_layout(b);
            break;
        case 1: //Configuration
         //   build_passive(b);
            break;
        case 2: //Setup
        //    build_active1(b);
       //   build_active2(b);
      //    build_active3(b);
            break;
        case 3: //Info
        //    build_pairs(b);
            break;
        
    }
}



