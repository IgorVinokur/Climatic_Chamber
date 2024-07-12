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
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Menu");

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

void displaySubMenuScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Setup");

  const char* subMenuItems[] = { "Param 1", "Param 2", "Param 3", "Param 4", "Back" };
  for (int i = 0; i < 5; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(subMenuItems[i]);
  }
}

void displaySetupScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Setup");

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
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Configuration");

  const char* configItems[] = { "Temperature Control", "Humidity Control", "Drainage", "Ventilation", "Quartz Lamp", "Back" };
  for (int i = topSubMenuItem; i < min(topSubMenuItem + itemsPerPage, 6); i++) {
    tft.setCursor(10, 40 + ((i - topSubMenuItem) * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(configItems[i]);
  }
}

void displayInfoScreen() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10, 10);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Setup");

  const char* subMenuItems[] = { "Version", "IP:", "Param3", "Param 4", "Back" };
  for (int i = 0; i < 5; i++) {
    tft.setCursor(10, 40 + (i * 30));
    if (i == selectedSubMenuItem) {
      tft.setTextColor(ST77XX_RED);
    } else {
      tft.setTextColor(ST77XX_WHITE);
    }
    tft.print(subMenuItems[i]);
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
      tft.print(mydata.sw_tempmode ? "Cooling" : "Heating");
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
