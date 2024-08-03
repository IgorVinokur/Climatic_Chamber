#pragma once

#define GH_INCLUDE_PORTAL
#define GH_NO_FS
//#define GH_NO_HTTP_PUBLIC         // отключить доступ к файлам по http c ip/www (для esp)
//#define GH_NO_HTTP_FETCH          // отключить скачивание файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD         // отключить загрузку файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD_PORTAL  // отключить упрощённую загрузку файлов с ip/hub/upload_portal (для esp)
#include <GyverHub.h>
GyverHub hub("MyDevices", "Climatic Chember", "f017");
//*******************************************************DashBoard*****************************************************************
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
    b.Gauge_("temp").label(F("Temperature")).noTab(1).size(2).value(String(temperature)).range(10, 90, 5).unit("℃").color(0x25b18f);
    b.Gauge_("hum").label("Humidity").noTab(1).size(2).value(String(humidity)).range(10, 90, 5).unit("%").color(0x25b18f);
    // if (b.Button().label("value").size(1).click()) hub.update("gag").value(random(100));
    // if (b.Button().label("range").click()) hub.update("gag").range(10, 90, 5);
    // if (b.Button().label("unit").click()) hub.update("gag").unit("deg");
    //if (b.Button().label("color").click()) hub.update("gag").color(rndColor());
    static gh::Timer tmr(2000);
         if (tmr) {
          b.refresh();
         }
  }
}
//++++++++++++++++++++++++++++++++++++++Settings***********************************************************************************
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

//**********************Configuration***************************************************************
void build_config(gh::Builder& b) {
  //    //build_common(b);
  bool flag_tempC = 0;
  bool flag_humC = 0;
  bool flag_drainC = 0;
  bool flag_airCirc = 0;
  bool flag_ventaC = 0;
  bool flag_qlampC = 0;
  b.Title("Configuration").fontSize(20);
  {
        gh::Row r(b);
        b.Title("  Temperature Control  ").align(gh::Align(1)).fontSize(16);
        //b.Title_("empt1", "   ").disabled(1).noTab(1).noLabel(1).size(3);
        b.Switch(&mydata.sw_temp).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_tempC);
  }
  if (mydata.sw_temp) {
  {
        gh::Row r(b);
            b.Spinner_("tmp", &mydata.temp).noTab(1).label("Temp. °С:").align(gh::Align(2)).size(3).range(10, 30, 1).attach(&flag_tempC);
            b.Spinner_("tmp_hys", &mydata.temp_hys).noTab(1).label("Hysteresis °C").align(gh::Align(2)).size(3).range(0, 10, 1).attach(&flag_tempC);
            b.Switch(&mydata.sw_tempmode).label("Heating Mode:").align(gh::Align(2)).noTab(1).attach(&flag_tempC); 
        if (flag_tempC) {
          b.refresh();
          data.update();        
        }
  }     
     }
//                 ############### Humidity Control ####################
 {
        gh::Row r(b);
        b.Title("Humidity Control %").align(gh::Align(1)).fontSize(16);
        b.Switch(&mydata.sw_humidity).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_humC);
  }
  if (mydata.sw_humidity) {
  {
        gh::Row r(b);
          
            b.Spinner_("set_hum", &mydata.set_humidity).noTab(1).label("Humidity %:").align(gh::Align(2)).size(3).range(30, 90, 5).attach(&flag_humC);
            b.Spinner_("hum_hys", &mydata.humidity_hys).noTab(1).label("Hysteresis %:").align(gh::Align(2)).size(3).range(0, 30, 1).attach(&flag_humC);    
        } if (flag_humC) {
          b.refresh();
          data.update();        
        }     
     }
//                 ############### Draining Control ####################
 {
        gh::Row r(b);
        b.Title("Draining Control %").align(gh::Align(1)).fontSize(16);
        b.Switch(&mydata.sw_draining).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_drainC);
  }
  if (mydata.sw_draining) {
  {
        gh::Row r(b);
            b.Spinner_("set_drain", &mydata.set_draining).noTab(1).label("Draining %:").align(gh::Align(2)).size(3).range(30, 90, 5).attach(&flag_drainC);
            b.Spinner_("drain_hys", &mydata.draining_hys).noTab(1).label("Hysteresis %:").align(gh::Align(2)).size(3).range(0, 30, 1).attach(&flag_drainC);    
        } if (flag_drainC) {
          b.refresh();
          data.update();        
        }     
     }
//                 ###############Air Circulation ####################
{
        gh::Row r(b);
        b.Title("Air Circulation").align(gh::Align(1)).fontSize(16);
        b.Switch(&mydata.sw_a_circulation).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_airCirc);
  }
   if (mydata.sw_a_circulation) {
  {
        gh::Row r(b);
            b.Spinner_("air_circ_period", &mydata.air_circ_Period).noTab(1).label("Period Hrs:").align(gh::Align(2)).size(3).range(1, 24, 1).attach(&flag_airCirc);
            b.Spinner_("air_circ_duration", &mydata.air_circ_Duration).noTab(1).label("Duration Min:").align(gh::Align(2)).size(3).range(1, 60, 1).attach(&flag_airCirc);
    }{
        gh::Row r(b);
            b.Slider_("air_circ_fan_pwr", &mydata.air_circ_fan_pwr).noTab(1).label("Fan speed:").size(3).range (0, 100, 1).attach(&flag_airCirc);
    }     
         if (flag_airCirc) {
          b.refresh();
          data.update();        
        }     
     }
//                 ############### Ventilation Control ####################
 {
        gh::Row r(b);
        b.Title("Ventilation Control").align(gh::Align(1)).fontSize(16);
        b.Switch(&mydata.sw_ventilation).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_drainC);
  }
  if (mydata.sw_ventilation) {
  {
        gh::Row r(b);
            b.Spinner_("venta_Period", &mydata.venta_Period).noTab(1).label("Period Hrs:").align(gh::Align(2)).size(3).range(30, 90, 5).attach(&flag_ventaC);
            b.Spinner_("venta_Duration", &mydata.venta_Duration).noTab(1).label("Duration Min:").align(gh::Align(2)).size(3).range(0, 30, 1).attach(&flag_ventaC);    
        } if (flag_ventaC) {
          b.refresh();
          data.update();        
        }     
     }
//                 ############### Quartz Lamp Control ####################
 {
        gh::Row r(b);
        b.Title("Quartz Lamp Control").align(gh::Align(1)).fontSize(16);
        b.Switch(&mydata.sw_q_lamp).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_qlampC);
  }
  if (mydata.sw_q_lamp) {
  {
        gh::Row r(b);
            b.Spinner_("qlamp_Period", &mydata.quartz_Period).noTab(1).label("Period Hrs:").align(gh::Align(2)).size(3).range(1, 24, 1).attach(&flag_qlampC);
            b.Spinner_("qlamp_Duration", &mydata.quartz_Duration).noTab(1).label("Duration Min:").align(gh::Align(2)).size(3).range(1, 60, 1).attach(&flag_qlampC);    
        } if (flag_qlampC) {
          b.refresh();
          data.update();        
        }     
     }

}



void updateTick() {
    if (hub.menu == 0) {
        static gh::Timer tmr(2000);
        if (tmr) {
            gh::Update upd(&hub);
            upd.update("temp").value(String(temperature));
            upd.update("hum").value(String(humidity));
            upd.send();
            

            //hub.sendUpdate("lbl3");
        }
    }
}


void build(gh::Builder& b) {
  // if (b.build.isSet()) hlog.println(b.build.name);
  b.Menu(F("Dashboard;Configuration;Setup"));

  switch (hub.menu) {
    case 0:  //Dashboard
      build_dashboard(b);
      //build_layout(b);
      break;
    case 1:  //Configuration
        build_config(b);
      break;
    case 2:  //Setup
      build_settings(b);
      //   build_active2(b);
      //    build_active3(b);
      break;
    
  }
}
