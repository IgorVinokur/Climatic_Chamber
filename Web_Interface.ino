// конструктор WEB страницы
void build() {
  GP.BUILD_BEGIN(700);
  GP.THEME(GP_DARK);
  GP.ICON_SUPPORT();

  GP.PAGE_TITLE("Smocker");
  GP.ONLINE_CHECK();
  GP.UPDATE("nowDate,nowTime,startTime,stopTime,tempr,humid,releIndikator,sw_temp_enable,sw_humidity_enable,temp,temp_hys,tempmode_enable");
  GP.TITLE("Smocker", "t1");
  
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
        if (data.sw_temp) {
            GP_MAKE_BOX(GP.PLAIN("Temp. °С:"); GP.SPINNER("temp", data.temp, 5, 30, 0.5, 1, GP_GREEN, "60pix" ));
            GP_MAKE_BOX(GP.PLAIN("Hysteresis °C:"); GP.SPINNER("temp_hys", data.temp_hys, 0, 10, 0.5, 1, GP_GREEN, "60pix"));
            GP_MAKE_BOX(GP.PLAIN("Heating Mode: "); GP.SWITCH("sw_tempmode", data.sw_tempmode));
            } 
        GP.PLAIN("Enable:");GP.SWITCH("sw_temp", data.sw_temp););
        

      GP_MAKE_BLOCK_THIN_TAB(
        "Humidity Control %",
        if (data.sw_humidity) {
            GP_MAKE_BOX(GP.PLAIN("Humidity %:"); GP.SPINNER("humidity", data.humidity, 40, 90, 1, 0, GP_GREEN, "60pix" )); 
            GP_MAKE_BOX(GP.PLAIN("Hysteresis %:  "); GP.SPINNER("humidity_hys", data.humidity_hys, 0, 10, 1, 0, GP_GREEN, "60pix" ));
            } 
        GP.PLAIN("Enable:"); GP.SWITCH("sw_humidity", data.sw_humidity);
        );
        );

      GP_MAKE_GRID(
      GP_MAKE_BLOCK_THIN_TAB(
        "Drainage %",
        if (data.sw_drainage) {
        GP_MAKE_BOX(GP.PLAIN("Drainage %:"); GP.SPINNER("drainage", data.drainage, 40, 90, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Hysteresis %:"); GP.SPINNER("drainage_hys", data.drainage_hys, 0, 10, 1, 0, GP_GREEN, "60pix"));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_drainage", data.sw_drainage););

      GP_MAKE_BLOCK_THIN_TAB(
        "Air Circulation",
        if (data.sw_a_circulation) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:");GP.SPINNER("air_circulation_Hours", data.air_circulation_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("circulation_work_time", data.circulation_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Fan:"); GP.SLIDER("fan_pwr", data.fan_pwr, 0, 100, 1));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_a_circulation", data.sw_a_circulation);
      );
      );
      
      GP_MAKE_GRID(
      GP_MAKE_BLOCK_THIN_TAB(
        "Ventilation",
        if (data.sw_ventilation) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:"); GP.SPINNER("venta_Hours", data.venta_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("venta_work_time", data.venta_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
        }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_ventilation", data.sw_ventilation);
      );

      GP_MAKE_BLOCK_THIN_TAB(
        "Quartz Lamp",
         if (data.sw_q_lamp) {
        GP_MAKE_BOX(GP.PLAIN("Period Hrs:"); GP.SPINNER("quartz_Hours", data.quartz_Hours, 1, 24, 1, 0, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Duration Min:"); GP.SPINNER("quartz_work_time", data.quartz_work_time, 1, 60, 1, 0, GP_GREEN, "60pix"));
         }
        GP.PLAIN("Enable:"); GP.SWITCH("sw_q_lamp", data.sw_q_lamp);
      );
      );

      

    );
  } else if (ui.uri() == "/setup") {

    // ===================== Setup =====================

    GP_MAKE_FORM(
      "/setup", "SAVE",
      GP_MAKE_BLOCK_TAB(
        "Set TimeZone",
        GP_MAKE_BOX(GP.LABEL("GMT"); GP.NUMBER("gmt", "GMT", data.gmt)););

      GP_MAKE_BLOCK_TAB(
        "WiFi Configuration",
        GP_MAKE_BOX(GP.LABEL("SSID: "); GP.TEXT("ssid", "SSID", data.ssid));
        GP_MAKE_BOX(GP.LABEL("Pass: "); GP.TEXT("pass", "Pass", data.pass));
        GP_MAKE_BOX(GP.LABEL("AP SSID: "); GP.TEXT("ap_ssid", "AP SSID", data.AP_ssid));););

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
        GP_MAKE_BOX(GP.PLAIN("Temp. Offset °C");GP.SPINNER("tempOffset", data.tempOffset, 0, 10, 0.5, 1, GP_GREEN, "60pix"));
        GP_MAKE_BOX(GP.PLAIN("Humidity Offset %"); GP.SPINNER("humidityOffset", data.humidityOffset, 0, 20, 1, 0, GP_GREEN, "60pix"));

      );

  } else if (ui.uri() == "/info") {

    GP_MAKE_BLOCK_TAB(
      "Connection Info",
      GP.LABEL("WiFi mode: ");
      GP.LABEL_BLOCK(WiFi.getMode() == WIFI_AP ? "AP" : "STA"); GP.BREAK(); GP.BREAK();

      GP.LABEL("Time synced");
      GP.LED("leds", ntp.synced()); GP.BREAK();
      //GP_MAKE_BOX(GP.LABEL("Time Zone"); GP.LABEL(data.gmt, "gmt"));
      GP.TIME("nowTime", nowTime);
      GP.DATE("nowDate", nowDate););



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
    GP.TIME("startTime", data.startTime);
    GP.BREAK();
    GP.LABEL("и выключим после: ");
    GP.TIME("stopTime", data.stopTime);
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Либо включать по температуре ");
    GP.SWITCH("sw", data.dependbyTempr);
    GP.BREAK();
    GP.LABEL("включать нагрузку при: ");
    GP.NUMBER("minTempr", "number", data.minTempr);
    GP.LABEL("°С");
    GP.BREAK();
    GP.LABEL("отключать при: ");
    GP.NUMBER("maxTempr", "number", data.maxTempr);
    GP.LABEL("°С");
    GP.BREAK();
    GP.BREAK();
    GP.LABEL("Реле 1:");
    GP.LED_RED("releIndikator", data.rele_1_isOn);
    GP.BREAK();
    //  GP.BUTTON("btn", "Вкл / Откл");
    //  GP.BREAK();
    //  GP.BREAK();
  }

  GP.BUILD_END();
}
