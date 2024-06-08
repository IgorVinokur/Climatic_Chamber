void displayInit() {

  tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);  // Use 320x170 color display
  tft.setRotation(1);                       // Rotate display if needed
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(60, 20);
  tft.setTextSize(3);
  tft.println("Welcome ");
  tft.setCursor(10, 50);
  tft.setTextSize(2);
  tft.println("Climatic Chamber v0.1 ");

  delay(5000); 
  tft.fillScreen(ST77XX_BLACK);
  MainDisplay();

}

void MainDisplay() {

  mainDisplay = 1;
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(130, 10);
  tft.setTextSize(2);
  tft.println(ntp.timeString());
  tft.setCursor(1, 40);
  tft.println("Temp:" + String(temperature) + "*C " + "Hum:" + String(humidity) + " %" );
  tft.setCursor(10, 80);
  //tft.println("Humidity: " + String(humidity) + " %");
  //tft.fillScreen(ST77XX_BLACK);
}