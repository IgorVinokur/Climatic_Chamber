// конструктор WEB страницы
void build() {
  GP.BUILD_BEGIN(700);
  GP.THEME(GP_DARK);
  GP.ICON_SUPPORT();

  GP.PAGE_TITLE("Climatic Chamber Controller");
  //GP.ONLINE_CHECK();
  GP.UPDATE("nowDate,nowTime,startTime,stopTime,tempr,humid,releIndikator,sw_temp_enable,sw_humidity_enable,temp,temp_hys,tempmode_enable");
  GP.TITLE("Climatic Chamber Controller", "t1");
  
  GP.HR();

  GP.NAV_TABS_LINKS("/,/cfg,/setup,/info,", "Home,Config,Setup,info");

  if (ui.uri() == "/cfg") {
    GP.GRID_RESPONSIVE(700);
    

    GP_MAKE_FORM(
      "/cfg", "SAVE",
      GP.RELOAD_CLICK("sw_temp,sw_humidity,sw_drainage,sw_a_circulation,sw_ventilation,sw_q_lamp"); 
      GP_MAKE_GRID(
      GP_MAKE_BLOCK_THIN_TAB(
        "Temperature Control °С",
        if (mydata.sw_temp) {
            GP_MAKE_BOX(GP.PLAIN("Temp. °С:"); GP.SPINNER("temp", mydata.temp, 5, 30, 1, 1, GP_GREEN, "60pix" ));
            GP_MAKE_BOX(GP.PLAIN("Hysteresis °C:"); GP.SPINNER("temp_hys", mydata.temp_hys, 0, 10, 1, 1, GP_GREEN, "60pix"));
            GP_MAKE_BOX(GP.PLAIN("Heating Mode: "); GP.SWITCH("sw_tempmode", mydata.sw_tempmode));
            } 
        GP.PLAIN("Enable:");GP.SWITCH("sw_temp", mydata.sw_temp););
        

      GP_MAKE_BLOCK_THIN_TAB(
        "Humidity Control %",
        if (mydata.sw_humidity) {
            GP_MAKE_BOX(GP.PLAIN("Humidity %:"); GP.SPINNER("set_humidity", mydata.set_humidity, 40, 90, 1, 0, GP_GREEN, "60pix" )); 
            GP_MAKE_BOX(GP.PLAIN("Hysteresis %:  "); GP.SPINNER("humidity_hys", mydata.humidity_hys, 0, 10, 1, 0, GP_GREEN, "60pix" ));
            } 
        GP.PLAIN("Enable:"); GP.SWITCH("sw_humidity", mydata.sw_humidity);
        );
        );

      GP_MAKE_GRID(
      GP_MAKE_BLOCK_THIN_TAB(
        "Drainage %",
        if (mydata.sw_drainage) {
        GP_MAKE_BOX(GP.PLAIN("Drainage %:"); GP.SPINNER("drainage", mydata.drainage, 40, 90, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Hysteresis %:"); GP.SPINNER("drainage_hys", mydata.drainage_hys, 0, 10, 1, 0, GP_GREEN, "60pix"));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_drainage", mydata.sw_drainage););

      GP_MAKE_BLOCK_THIN_TAB(
        "Air Circulation",
        if (mydata.sw_a_circulation) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:");GP.SPINNER("air_circulation_Hours", mydata.air_circulation_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("circulation_work_time", mydata.circulation_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Fan:"); GP.SLIDER("fan_pwr", mydata.fan_pwr, 0, 100, 1));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_a_circulation", mydata.sw_a_circulation);
      );
      );
      
      GP_MAKE_GRID(
      GP_MAKE_BLOCK_THIN_TAB(
        "Ventilation",
        if (mydata.sw_ventilation) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:"); GP.SPINNER("venta_Hours", mydata.venta_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("venta_work_time", mydata.venta_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_ventilation", mydata.sw_ventilation);
      );

      GP_MAKE_BLOCK_THIN_TAB(
        "Quartz Lamp",
         if (mydata.sw_q_lamp) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:"); GP.SPINNER("quartz_Hours", mydata.quartz_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("quartz_work_time", mydata.quartz_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
         }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_q_lamp", mydata.sw_q_lamp);
      );
      );

      

    );
  } else if (ui.uri() == "/setup") {

    // ===================== Setup =====================

    GP_MAKE_FORM(
      "/setup", "SAVE",
      GP_MAKE_BLOCK_TAB(
        "Set TimeZone",
        GP_MAKE_BOX(GP.LABEL("GMT"); GP.NUMBER("gmt", "GMT", mydata.gmt)););

      GP_MAKE_BLOCK_TAB(
        "WiFi Configuration",
        GP_MAKE_BOX(GP.LABEL("SSID: "); GP.TEXT("ssid", "SSID", mydata.staSsid));
        GP_MAKE_BOX(GP.LABEL("Pass: "); GP.PASS_EYE("pass", "Password", mydata.staPass));
        GP_MAKE_BOX(GP.LABEL("AP SSID: "); GP.TEXT("ap_ssid", "AP SSID", mydata.apSsid));
        GP_MAKE_BOX(GP.LABEL("AP Pass: "); GP.TEXT("ap_pass", "AP Password", mydata.apPass));
        ););


    GP_MAKE_BLOCK_THIN_TAB(
      "File Manager",
      GP.LABEL("File/Files/Fldr");
      GP_MAKE_BOX(
        GP_CENTER,
        GP.FILE_UPLOAD("");
        GP.FILE_UPLOAD("");
        GP.FOLDER_UPLOAD("");););

    GP_MAKE_BLOCK_THIN_TAB(
      "OTA Firmware",
      GP_MAKE_BOX(
        GP_CENTER,
        GP.OTA_FIRMWARE();
        GP.OTA_FILESYSTEM();););
    //все обновляющиеся параметры на WEB странице надо указать тут
    GP_MAKE_BLOCK_THIN_TAB(
        "Calibration Offsets",
        GP_MAKE_BOX(GP.PLAIN("Temp. Offset °C");GP.SPINNER("tempOffset", mydata.tempOffset, -10, 10, 1, 1, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Humidity Offset %"); GP.SPINNER("humidityOffset", mydata.humidityOffset, 0, 20, 1, 0, GP_GREEN, "60pix"));

      );
    GP_MAKE_BLOCK_THIN_TAB(
        "Reset",
        GP_MAKE_BOX(GP.BUTTON_MINI("espRestart", "Restart"));
      ); 


  } else if (ui.uri() == "/info") {

    GP_MAKE_BLOCK_TAB(
      "Connection Info",
     // GP.LABEL("WiFi mode: ");
     // GP.LABEL_BLOCK(WiFi.getMode() == WIFI_AP ? "AP" : "STA"); GP.BREAK(); GP.BREAK();

     // GP.LABEL("Time synced");
      //GP.LED("leds", ntp.synced()); GP.BREAK();
      
      //GP.TIME("nowTime", nowTime);
      //GP.DATE("nowDate", nowDate);
      GP.SYSTEM_INFO(); GP.BREAK(););
      



  } else {

    // ================================  HOME =======================
    GP.LABEL("Сегодня: ");
    GP.BREAK();
    GP.DATE("nowDate", nowDate);
    GP.TIME("nowTime", nowTime);
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("BME280 параметры ");
    GP.BREAK();
    //GP.ICON(thermometer-full);
    GP.LABEL(GP.ICON("thermometer-three-quarters") + "Температура: ");
    GP.LABEL("tempr", "tempr");
    GP.LABEL("°С");
    GP.BREAK();
    GP.LABEL(GP.ICON("tint") + "Влажность: ");
    GP.LABEL("humid", "humid");
    GP.LABEL("%");
    GP.BREAK();
    GP.BREAK();
    GP.HR();
    GP.LABEL("Включим нагрузку в: ");
    GP.TIME("startTime", mydata.startTime);
    GP.BREAK();
    GP.LABEL("и выключим после: ");
    GP.TIME("stopTime", mydata.stopTime);
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Либо включать по температуре ");
    GP.SWITCH("sw", mydata.dependbyTempr);
    GP.BREAK();
    GP.LABEL("включать нагрузку при: ");
    GP.NUMBER("minTempr", "number", mydata.minTempr);
    GP.LABEL("°С");
    GP.BREAK();
    GP.LABEL("отключать при: ");
    GP.NUMBER("maxTempr", "number", mydata.maxTempr);
    GP.LABEL("°С");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Реле 1:");
    GP.LED_RED("releIndikator", mydata.rele_1_isOn);
    GP.BREAK();
    //  GP.BUTTON("btn", "Вкл / Откл");
    //  GP.BREAK();
    //  GP.BREAK();
  }

  GP.BUILD_END();
}
