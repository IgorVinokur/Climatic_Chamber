void action() {
  // было обновление
  if (ui.update()) {
  
    ui.updateDate("nowDate", nowDate);
    ui.updateTime("nowTime", nowTime);
    ui.updateTime("startTime", data.startTime);
    ui.updateTime("stopTime", data.stopTime);
    ui.updateInt("tempr", temperature);
    ui.updateInt("humid", humidity);

    
  }  //ui.update()
  // был клик по компоненту внутри веб странички
  
  // ================== CONFIG ==================
  if (ui.form()) {
    if (ui.form("/cfg")) {
      eemem.update();
      ui.copyFloat("temp", data.temp);
      ui.copyFloat("temp_hys", data.temp_hys);
      ui.copyInt("humidity", data.humidity);
      ui.copyInt("humidity_hys", data.humidity_hys);
      ui.copyInt("drainage", data.drainage);
      ui.copyInt("drainage_hys", data.drainage_hys);
      ui.copyInt("air_circulation_Hours", data.air_circulation_Hours);
      ui.copyInt("circulation_work_time", data.circulation_work_time);
      ui.copyFloat("fan_pwr", data.fan_pwr);
      ui.copyInt("venta_Hours", data.venta_Hours);
      ui.copyInt("venta_work_time", data.venta_work_time);
      ui.copyInt("quartz_Hours", data.quartz_Hours);
      ui.copyInt("quartz_work_time", data.quartz_work_time);
      ui.copyFloat("tempOffset", data.tempOffset);
      ui.copyInt("humidityOffset", data.humidityOffset);
      
    }
    else if (ui.form("/setup")) {
      eemem.update();
      ui.copyStr("ssid", data.ssid);
      ui.copyStr("pass", data.pass);
      ui.copyStr("ap_ssid", data.AP_ssid);
      ui.copyInt("gmt", data.gmt);
    }
  }  
  
  if (ui.click()) {
    if (ui.clickDate("nowDate", nowDate)) {
      //      Serial.print("Date: ");
      //      Serial.println(valDate.encode());
    }
    if (ui.clickTime("nowTime", nowTime)) {
      //      Serial.print("Time: ");
      //      Serial.println(valTime.encode());
    }
    // обновление времени запуска и отключения нагрузки
    if (ui.clickTime("startTime", data.startTime)) {
      startSeconds = data.startTime.hour * 60 * 60 + data.startTime.minute * 60 + data.startTime.second;
      eemem.update();
    }
    if (ui.clickTime("stopTime", data.stopTime)) {
      stopSeconds = data.stopTime.hour * 60 * 60 + data.stopTime.minute * 60 + data.stopTime.second;
      eemem.updateNow();
    }
    if (ui.clickBool("sw", data.dependbyTempr)) {
      eemem.updateNow();
    }
     if (ui.clickBool("sw_temp", data.sw_temp)) {
      eemem.updateNow();
    }
     if (ui.clickBool("sw_tempmode", data.sw_tempmode)) {
      eemem.updateNow();
     }
    if (ui.clickBool("sw_humidity", data.sw_humidity)) {
      eemem.updateNow();
    }
    if (ui.clickBool("sw_drainage", data.sw_drainage)) {
      eemem.updateNow();
    }
    if (ui.clickBool("sw_a_circulation", data.sw_a_circulation)) {
      eemem.updateNow();
    }
    if (ui.clickBool("sw_ventilation", data.sw_ventilation)) {
      eemem.updateNow();
    }
    if (ui.clickBool("sw_q_lamp", data.sw_q_lamp)) {
      eemem.updateNow();
    }

    if (ui.clickInt("maxTempr", data.maxTempr)) {
      eemem.updateNow();
    }
    if (ui.clickInt("minTempr", data.minTempr)) {
      eemem.updateNow();
    }
    if (ui.clickInt("tempOffset", data.tempOffset)) {
      eemem.updateNow();
    }
      if (ui.clickInt("humidityOffset", data.humidityOffset)) {
      eemem.updateNow();
    }


    if (ui.click("btn")) {
      data.rele_1_isOn = !data.rele_1_isOn;
      if (data.rele_1_isOn) digitalWrite(RELE1, ON);
      else digitalWrite(RELE1, OFF);
      eemem.updateNow();
    }
    if (ui.clickDown("espRestart")) {
      Serial.println("Controller Restart");
      ESP.restart();
    }
    
  }  //ui.click()
}  //action()
