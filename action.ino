void action() {
  // было обновление
  if (ui.update()) {
  
    ui.updateDate("nowDate", nowDate);
    ui.updateTime("nowTime", nowTime);
    ui.updateTime("startTime", mydata.startTime);
    ui.updateTime("stopTime", mydata.stopTime);
    ui.updateInt("tempr", temperature);
    ui.updateInt("humid", humidity);

    
  }  //ui.update()
  // был клик по компоненту внутри веб странички
  
  // ================== CONFIG ==================
  if (ui.form()) {
    if (ui.form("/cfg")) {
      data.update();
      ui.copyFloat("temp", mydata.temp);
      ui.copyFloat("temp_hys", mydata.temp_hys);
      ui.copyInt("humidity", mydata.humidity);
      ui.copyInt("humidity_hys", mydata.humidity_hys);
      ui.copyInt("drainage", mydata.drainage);
      ui.copyInt("drainage_hys", mydata.drainage_hys);
      ui.copyInt("air_circulation_Hours", mydata.air_circulation_Hours);
      ui.copyInt("circulation_work_time", mydata.circulation_work_time);
      ui.copyFloat("fan_pwr", mydata.fan_pwr);
      ui.copyInt("venta_Hours", mydata.venta_Hours);
      ui.copyInt("venta_work_time", mydata.venta_work_time);
      ui.copyInt("quartz_Hours", mydata.quartz_Hours);
      ui.copyInt("quartz_work_time", mydata.quartz_work_time);
      ui.copyFloat("tempOffset", mydata.tempOffset);
      ui.copyInt("humidityOffset", mydata.humidityOffset);
      
    }
    else if (ui.form("/setup")) {
      data.update();
      ui.copyStr("ssid", mydata.ssid);
      ui.copyStr("pass", mydata.pass);
      ui.copyStr("ap_ssid", mydata.AP_ssid);
      ui.copyInt("gmt", mydata.gmt);
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
    if (ui.clickTime("startTime", mydata.startTime)) {
      startSeconds = mydata.startTime.hour * 60 * 60 + mydata.startTime.minute * 60 + mydata.startTime.second;
      data.update();
    }
    if (ui.clickTime("stopTime", mydata.stopTime)) {
      stopSeconds = mydata.stopTime.hour * 60 * 60 + mydata.stopTime.minute * 60 + mydata.stopTime.second;
      data.update();
    }
    if (ui.clickBool("sw", mydata.dependbyTempr)) {
      data.update();
    }
     if (ui.clickBool("sw_temp", mydata.sw_temp)) {
      data.update();
    }
     if (ui.clickBool("sw_tempmode", mydata.sw_tempmode)) {
      data.update();
     }
    if (ui.clickBool("sw_humidity", mydata.sw_humidity)) {
      data.update();
    }
    if (ui.clickBool("sw_drainage", mydata.sw_drainage)) {
      data.update();
    }
    if (ui.clickBool("sw_a_circulation", mydata.sw_a_circulation)) {
      data.update();
    }
    if (ui.clickBool("sw_ventilation", mydata.sw_ventilation)) {
      data.update();
    }
    if (ui.clickBool("sw_q_lamp", mydata.sw_q_lamp)) {
      data.update();
    }

    if (ui.clickInt("maxTempr", mydata.maxTempr)) {
      data.update();
    }
    if (ui.clickInt("minTempr", mydata.minTempr)) {
      data.update();
    }
    if (ui.clickFloat("tempOffset", mydata.tempOffset)) {
      data.update();
    }
      if (ui.clickInt("humidityOffset", mydata.humidityOffset)) {
      data.update();
    }


    if (ui.click("btn")) {
      mydata.rele_1_isOn = !mydata.rele_1_isOn;
      if (mydata.rele_1_isOn) digitalWrite(RELE1, ON);
      else digitalWrite(RELE1, OFF);
      data.update();
    }
    if (ui.click("espRestart")) {
      Serial.println("Controller Restart");
      ESP.restart();
    }
    
  }  //ui.click()
}  //action()
