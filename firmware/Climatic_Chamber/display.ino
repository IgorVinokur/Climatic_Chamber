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
  tft.setTextSize(2);
  tft.setCursor(130, 10);
    //tft.println(ntp.timeString());
  tft.drawLine(1, 30, 320, 30, ST77XX_YELLOW);
  tft.drawLine(220, 31, 220, 170, ST77XX_GREEN);
  tft.drawLine(220, 100, 320, 100, ST77XX_GREEN);
  //tft.setCursor(10, 80);
  //tft.println("Humidity: " + String(humidity) + " %");
  //tft.fillScreen(ST77XX_BLACK);
}