#pragma once
#define GH_INCLUDE_PORTAL
#include <GyverHub.h>

GyverHub hub("MyDevices", "Climatic Chember", "");


//void build(gh::Builder& b) {
//    if (b.Switch().click()) digitalWrite(LED_BUILTIN, !b.build.value);
//}

void build(gh::Builder& b) {
   // if (b.build.isSet()) hlog.println(b.build.name);
    b.Menu(F("Basic;Passive;Active;Pairs;From file;Widget;MQTT;Popup;Canvas;Update;Location"));

    switch (hub.menu) {
        case 0:
          //  build_widget(b);
           // build_layout(b);
            break;
        case 1:
         //   build_passive(b);
            break;
        case 2:
        //    build_active1(b);
       //   build_active2(b);
      //    build_active3(b);
            break;
        case 3:
        //    build_pairs(b);
            break;
        case 4:
         //   build_ffile(b);
            break;
        case 5:
       //     build_custom(b);
            break;
        case 6:
        //    build_mqtt(b);
            break;
        case 7:
        //    build_popup(b);
            break;
        case 8:
        //    build_canvas(b);
            break;
        case 9:
       //     build_update(b);
            break;
        case 10:
       //     build_location(b);
            break;
    }
}