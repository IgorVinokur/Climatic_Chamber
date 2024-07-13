void displayInit() {
  tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);  // Use 320x170 color display
  tft.setRotation(1);                       // Rotate display if needed
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(70, 20);
  tft.setTextSize(3);
  tft.println("Welcome ");
  tft.setCursor(20, 50);
  tft.setTextSize(2);
  tft.println("Climatic Chamber v0.1 ");
  delay(5000);
  tft.fillScreen(ST77XX_BLACK);
  displayMainScreen();
  lastInteractionTime = millis();  // Initialize last interaction time
}


void displayMainScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(130, 10);
  //tft.println(ntp.timeString());
  tft.drawLine(1, 30, 320, 30, ST77XX_YELLOW);
  tft.drawLine(220, 31, 220, 170, ST77XX_GREEN);
  tft.drawLine(220, 100, 320, 100, ST77XX_GREEN);
  if (WiFi.getMode() == WIFI_AP) {
    tft.drawBitmap(5, 8, nowireless, 20, 20, ST77XX_RED);
    tft.drawBitmap(40, 8, nocloud, 30, 20, ST77XX_RED);
  } else {
    tft.drawBitmap(5, 8, wireless, 20, 20, ST77XX_GREEN);
    tft.drawBitmap(40, 8, cloud, 30, 20, ST77XX_BLUE);
  }


  //tft.setCursor(10, 80);
  //tft.println("Humidity: " + String(humidity) + " %");
  //tft.fillScreen(ST77XX_BLACK);
}

void clockDisplay() {
  tft.fillRect(200, 10, 270, 15, ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(220, 10);
  tft.println(ntp.timeString());
}

void sensorsDisplay() {
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(230, 35);
  tft.println("Temp");
  tft.fillRect(240, 65, 40, 30, ST77XX_BLACK);  //clear Temperature value
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(240, 72);
  //previusTemp = temperature;
  //previusHum = humidity;
  tft.println(String(temperature) + "C");
  tft.setCursor(235, 110);
  tft.setTextSize(3);
  tft.println("Hum");
  tft.fillRect(240, 133, 40, 40, ST77XX_BLACK);  //clear Humidity value
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(240, 140);
  tft.println(String(humidity) + "%");
}
void displayMenuScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Menu **");
  tft.setTextColor(ST77XX_WHITE);
  const char* menuItems[] = { "Configuration", "Setup", "Info", "Back" };
  for (int i = topMenuItem; i < min(topMenuItem + itemsPerPage, 4); i++) {
    tft.setCursor(10, 40 + ((i - topMenuItem) * 30));
    if (i == selectedMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(menuItems[i]);
  }
}


void displaySetupScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Setup **");
  tft.setTextColor(ST77XX_WHITE);

  const char* setupItems[] = { "Temp. Offset", "Hum. Offset", "Restart", "Back" };
  for (int i = topSubMenuItem; i < min(topSubMenuItem + itemsPerPage, 4); i++) {
    tft.setCursor(10, 40 + ((i - topSubMenuItem) * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(setupItems[i]);
  }
}

void displayConfigurationScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Configuration **");
  tft.setTextColor(ST77XX_WHITE);

  const char* configItems[] = { "Temperature Control", "Humidity Control", "Draining", "Air Circulation", "Ventilation", "Quartz Lamp", "Back" };
  for (int i = topSubMenuItem; i < min(topSubMenuItem + itemsPerPage, 7); i++) {
    tft.setCursor(10, 40 + ((i - topSubMenuItem) * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(configItems[i]);
  }
}



void displayTempOffsetScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Temp. Sensor Offset **");

  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 50);
  tft.setTextSize(3);
  tft.print("Value: ");
  tft.print(mydata.tempOffset / 10.0, 1);  // Display as floating point with one decimal
}

void displayHumOffsetScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Hum. Sensor Offset **");

  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 50);
  tft.setTextSize(3);
  tft.print("Value: ");
  tft.print(mydata.humidityOffset, 1);  // Display as floating point with one decimal
}

void displayTempControlScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Temperature Control **");

  tft.setTextColor(ST77XX_WHITE);
  const char* tempControlItems[] = { "Enable", "Set Temperature", "Set Hysteresis", "Mode" };
  for (int i = 0; i < 4; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedTempControlItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(tempControlItems[i]);
    tft.print(": ");
    if (i == 0) {
      tft.print(mydata.sw_temp ? "ON" : "OFF");
    } else if (i == 1) {
      tft.print(mydata.temp);
    } else if (i == 2) {
      tft.print(mydata.temp_hys);
    } else if (i == 3) {
      tft.print(mydata.sw_tempmode ? "Heating" : "Cooling");
    }
  }
}

void displayHumControlScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Humidity Control **");

  tft.setTextColor(ST77XX_WHITE);
  const char* humControlItems[] = { "Enable", "Set Humidity", "Set Hysteresis" };
  for (int i = 0; i < 3; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedHumControlItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(humControlItems[i]);
    tft.print(": ");
    if (i == 0) {
      tft.print(mydata.sw_humidity ? "ON" : "OFF");
    } else if (i == 1) {
      tft.print(mydata.set_humidity);
    } else if (i == 2) {
      tft.print(mydata.humidity_hys);
    }
  }
}

void displayDrainingControlScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Draining Control **");

  tft.setTextColor(ST77XX_WHITE);
  const char* drainControlItems[] = { "Enable", "Set Draining", "Set Hysteresis" };
  for (int i = 0; i < 3; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedDrainControlItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(drainControlItems[i]);
    tft.print(": ");
    if (i == 0) {
      tft.print(mydata.sw_draining ? "ON" : "OFF");
    } else if (i == 1) {
      tft.print(mydata.set_draining);
    } else if (i == 2) {
      tft.print(mydata.draining_hys);
    }
  }
}

void displayACirculControlScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("*Air Circulation Control*");

  tft.setTextColor(ST77XX_WHITE);
  const char* a_circulControlItems[] = { "Enable", "Period Hrs.", "Duration Min.", "Fan Speed %" };
  for (int i = 0; i < 4; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedACirculControlItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(a_circulControlItems[i]);
    tft.print(": ");
    if (i == 0) {
      tft.print(mydata.sw_a_circulation ? "ON" : "OFF");
    } else if (i == 1) {
      tft.print(mydata.air_circulation_Period);
    } else if (i == 2) {
      tft.print(mydata.air_circulation_Duration);
    }  else if (i == 3) {
      tft.print(mydata.air_circulation_fan_pwr);
    }
  }
}


void displayInfoScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print("** Information **");
  tft.setTextColor(ST77XX_WHITE);

  const char* subInfoItems[] = { "Version", "IP:", "Param3", "Param 4", "Back" };
  for (int i = topSubMenuItem; i < min(topSubMenuItem + itemsPerPage, 5); i++) {
    tft.setCursor(10, 40 + ((i - topSubMenuItem) * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(subInfoItems[i]);
  }
}
