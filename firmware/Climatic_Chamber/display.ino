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
  MainDisplay();
}


void MainDisplay() {
  mainDisplay = 1;
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(130, 10);
  //tft.println(ntp.timeString());
  tft.drawLine(1, 30, 320, 30, ST77XX_YELLOW);
  tft.drawLine(220, 31, 220, 170, ST77XX_GREEN);
  tft.drawLine(220, 100, 320, 100, ST77XX_GREEN);
  if (WiFi.getMode() == WIFI_AP){
    tft.drawBitmap(5, 8, nowireless, 20, 20, ST77XX_RED);
    tft.drawBitmap(40, 8, nocloud, 20, 20, ST77XX_RED);
    } else {
      tft.drawBitmap(5, 8, wireless, 20, 20, ST77XX_GREEN);
      tft.drawBitmap(40, 8, cloud, 20, 20, ST77XX_BLUE);
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
 // float previusTemp;
 // float previusHum;
  //tft.setTextColor(ST77XX_BLACK);
  //tft.setCursor(235, 72);
  //tft.setTextSize(3);
  //tft.printf("%.2fC", previusTemp);
  //tft.println(String(previusTemp));
  //tft.setCursor(240, 140);
  //tft.printf("%.1f%%", previusHum);
  //tft.println(String(previusHum));
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(3);
  tft.setCursor(230, 35);
  tft.println("Temp");
   tft.fillRect(240, 65, 40, 30, ST77XX_BLACK); //clear Temperature value
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(240, 72);
  //previusTemp = temperature;
  //previusHum = humidity;
  tft.println(String(temperature) + "C");
  tft.setCursor(235, 110);
  tft.setTextSize(3);
  tft.println("Hum");
  tft.fillRect(240, 133, 40, 40, ST77XX_BLACK); //clear Humidity value
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(240, 140);
  tft.println(String(humidity) + "%");
}

