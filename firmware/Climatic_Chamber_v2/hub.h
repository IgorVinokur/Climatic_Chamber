#pragma once

#define GH_INCLUDE_PORTAL
#define GH_NO_FS
//#define GH_NO_HTTP_PUBLIC         // отключить доступ к файлам по http c ip/www (для esp)
//#define GH_NO_HTTP_FETCH          // отключить скачивание файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD         // отключить загрузку файлов по http (для esp)
//#define GH_NO_HTTP_UPLOAD_PORTAL  // отключить упрощённую загрузку файлов с ip/hub/upload_portal (для esp)
#include <GyverHub.h>
GyverHub hub;
//*******************************************************DashBoard*****************************************************************

void build_dashboard(gh::Builder& b) {
  b.Title("Dashboard");
  //{
  //  gh::Row r(b);
  //   b.Label_(ntp.timeString());
  //   b.Label_(ntp.dateString());
  //   hub.update(F("main")).label(ntp.timeString()).label(ntp.dateString());
 // }
  {
    gh::Row r(b);
    b.Gauge_("temp").label(F("Temperature")).noTab(1).size(2).value(String(temperature)).range(10, 90, 5).unit("℃").color(0x25b18f);
    b.Gauge_("hum").label(F("Humidity")).noTab(1).size(2).value(String(humidity)).range(10, 90, 5).unit("%").color(0x25b18f);
  }
  { gh::Row r(b); }

  {
    gh::Row r(b);
    b.Icon_("tempsts").noTab(0).icon(F(""));
    b.Icon_("humsts").noTab(0).icon(F(""));
    b.Icon_("drainsts").noTab(0).icon(F(""));
  }
  {
    gh::Row r(b);
    b.Icon_("a_cstat").noTab(0).icon(F(""));
    b.Icon_("ventastat").noTab(0).icon(F(""));
    b.Icon_("qlampstat").noTab(0).icon(F(""));
  }
}
//++++++++++++++++++++++++++++++++++++++Settings***********************************************************************************
void build_settings(gh::Builder& b) {
  //    //build_common(b);
  bool flag_w = 0;
  bool flag_rst = 0;
  bool flag_sensorsC = 0;
  bool flag_mqtt = 0;
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
  b.Title("Sensors Calibration").fontSize(20);
  {
    gh::Row r(b);
    b.Spinner_("tempOffset", &mydata.tempOffset).noTab(0).label(F("Temp. Offset °C")).align(gh::Align(1)).size(3).range(-10, 10, 1).attach(&flag_sensorsC);
    b.Spinner_("humidityOffset", &mydata.humidityOffset).noTab(0).label(F("Humidity Offset %")).align(gh::Align(3)).size(3).range(0, 20, 1).attach(&flag_sensorsC);
  }
  if (flag_sensorsC) {
    data.update();
  }

  b.Title("MQTT Settings").fontSize(20);
  {
    gh::Row r(b);
    b.Input_("mqttServer", mydata.mqttServer).label(F("MQTT Server")).size(4).attach(&flag_mqtt);
    b.Input_("mqttPort", &mydata.mqttPort).label(F("MQTT Port")).size(4).attach(&flag_mqtt);
  }
  {
    gh::Row r(b);
    b.Input_("mqttUser", mydata.mqttUser).label(F("MQTT User")).size(4).attach(&flag_mqtt);
    b.Pass_("mqttPwd", mydata.mqttPwd).label(F("MQTT Password")).size(4).attach(&flag_mqtt);
  }
  {
    gh::Row r(b);
    b.Input_("mqttTopic", mydata.mqttTopic).label(F("MQTT Topic")).size(4).attach(&flag_mqtt);
  }

  if (flag_mqtt) {
    data.update();
  }
  {
    gh::Row r(b);
    static gh::Button btn;
    b.Button_("btn").label(F("Save & Reboot")).noTab(0).attach(&flag_rst).fontSize(30).icon("");
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
    b.Title("Temperature Control").align(gh::Align(1)).fontSize(16);
    //b.Title_("empt1", "   ").disabled(1).noTab(1).noLabel(1).size(3);
    b.Switch(&mydata.sw_temp).noLabel(1).noTab(1).align(gh::Align(3)).attach(&flag_tempC);
  }
  if (mydata.sw_temp) {
    {
      gh::Row r(b);
      b.Spinner_("tmp", &mydata.temp).noTab(1).label(F("Temp. °С:")).align(gh::Align(2)).size(3).range(10, 30, 1).attach(&flag_tempC);
      b.Spinner_("tmp_hys", &mydata.temp_hys).noTab(1).label(F("Hysteresis °C")).align(gh::Align(2)).size(3).range(0, 10, 1).attach(&flag_tempC);
      b.Switch(&mydata.sw_tempmode).label(F("Heating Mode:")).align(gh::Align(2)).noTab(1).attach(&flag_tempC);
      if (flag_tempC) {
        temp_relay_heating.setpoint = mydata.temp;        // Update Temperature of cooling
        temp_relay_heating.hysteresis = mydata.temp_hys;  //Update Hysteresis of cooling
        temp_relay_cooling.setpoint = mydata.temp;        // Update Temperature of heating
        temp_relay_cooling.hysteresis = mydata.temp_hys;  // Update Hysteresis of heating
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

      b.Spinner_("set_hum", &mydata.set_humidity).noTab(1).label(F("Humidity %:")).align(gh::Align(2)).size(3).range(30, 90, 5).attach(&flag_humC);
      b.Spinner_("hum_hys", &mydata.humidity_hys).noTab(1).label(F("Hysteresis %:")).align(gh::Align(2)).size(3).range(0, 30, 1).attach(&flag_humC);
    }
    if (flag_humC) {
      data.update();
      b.refresh();
      hum_relay.setpoint = mydata.set_humidity;    // Set Humidity %
      hum_relay.hysteresis = mydata.humidity_hys;  // Set humidity Hysteresis %
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
      b.Spinner_("set_drain", &mydata.set_draining).noTab(1).label(F("Draining %:")).align(gh::Align(2)).size(3).range(30, 90, 5).attach(&flag_drainC);
      b.Spinner_("drain_hys", &mydata.draining_hys).noTab(1).label(F("Hysteresis %:")).align(gh::Align(2)).size(3).range(0, 30, 1).attach(&flag_drainC);
    }
    if (flag_drainC) {
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
      b.Spinner_("air_circ_period", &mydata.air_circ_Period).noTab(1).label(F("Period Hrs:")).align(gh::Align(2)).size(3).range(1, 24, 1).attach(&flag_airCirc);
      b.Spinner_("air_circ_duration", &mydata.air_circ_Duration).noTab(1).label(F("Duration Min:")).align(gh::Align(2)).size(3).range(1, 60, 1).attach(&flag_airCirc);
    }
    {
      gh::Row r(b);
      b.Slider_("air_circ_fan_pwr", &mydata.air_circ_fan_pwr).noTab(1).label(F("Fan speed:")).size(3).range(0, 100, 1).attach(&flag_airCirc);
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
      b.Spinner_("venta_Period", &mydata.venta_Period).noTab(1).label(F("Period Hrs:")).align(gh::Align(2)).size(3).range(1, 24, 1).attach(&flag_ventaC);
      b.Spinner_("venta_Duration", &mydata.venta_Duration).noTab(1).label(F("Duration Min:")).align(gh::Align(2)).size(3).range(1, 60, 1).attach(&flag_ventaC);
    }
    if (flag_ventaC) {
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
      b.Spinner_("qlamp_Period", &mydata.quartz_Period).noTab(1).label(F("Period Hrs:")).align(gh::Align(2)).size(3).range(1, 24, 1).attach(&flag_qlampC);
      b.Spinner_("qlamp_Duration", &mydata.quartz_Duration).noTab(1).label(F("Duration Min:")).align(gh::Align(2)).size(3).range(1, 60, 1).attach(&flag_qlampC);
    }
    if (flag_qlampC) {
      b.refresh();
      data.update();
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
void updateTick() {

  static gh::Timer tmr(5000);
  if (tmr) {
    gh::Update upd(&hub);
    upd.update("temp").value(String(temperature));
    upd.update("hum").value(String(humidity));
    upd.send();
    //hub.sendUpdate("lbl3");
  }
}

void dashboardiconStat() { //Update Status of icons on Dashboard
  // Temperature Icon
  if (mydata.sw_temp) {
    hub.update("tempsts").label(F("Temp. Control ON"));
    if (digitalRead(RELE_TEMP) == HIGH) {
      //Serial.println("Reley Temp. Is ON");
      hub.update("tempsts").value(1);
    } else {
      hub.update("tempsts").value(0);
     // Serial.println("Reley Temp. Is OFF");
    }
  } else {
    hub.update("tempsts").label(F("Temp. Control OFF"));
  }

  // Humidity Icon
  if (mydata.sw_humidity) {
    hub.update("humsts").label(F("Humidity Control ON"));
    if (digitalRead(RELE_HUM) == HIGH) {
      hub.update("humsts").value(1);
    } else {
      hub.update("humsts").value(0);
    }
  } else {
    hub.update("humsts").label(F("Humidity Control OFF"));
  }

  // Draining Icon
  if (mydata.sw_draining) {
    hub.update("drainsts").label(F("Draining Control ON"));
    if (digitalRead(RELE_DRAIN) == HIGH) {
      hub.update("drainsts").value(1);
    } else {
      hub.update("drainsts").value(0);
    }
  } else {
    hub.update("drainsts").label(F("Draining Control OFF"));
  }

  // Air Circulation Icon
  if (mydata.sw_a_circulation) {
    hub.update("a_cstat").label(F("Air Circulation Control ON"));
    if (digitalRead(RELE_A_CIRC) == HIGH) {
      hub.update("a_cstat").value(1);
    } else {
      hub.update("a_cstat").value(0);
    }
  } else {
    hub.update("a_cstat").label(F("Air Circulation Control OFF"));
  }

  // Ventilation Icon
  if (mydata.sw_ventilation) {
    hub.update("ventastat").label(F("Ventilation Control ON"));
    if (digitalRead(RELE_VENTA) == HIGH) {
      hub.update("ventastat").value(1);
    } else {
      hub.update("ventastat").value(0);
    }
  } else {
    hub.update("ventastat").label(F("Ventilation Control OFF"));
  }

  //Quarz Lamp Icon
  if (mydata.sw_q_lamp) {
    hub.update("qlampstat").label(F("QLamp Control ON"));
    if (digitalRead(RELE_Q_LAMP) == HIGH) {
      hub.update("qlampstat").value(1);
    } else {
      hub.update("qlampstat").value(0);
    }
  } else {
    hub.update("qlampstat").label(F("QLamp Control OFF"));
  }
}
