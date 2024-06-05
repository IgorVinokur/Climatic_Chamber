void displayInit() {

  tft.init(DISPLAY_WIDTH, DISPLAY_HEIGHT);  // Use 320x170 color display
  tft.setRotation(1);                       // Rotate display if needed
  tft.fillScreen(ST77XX_WHITE);
}

void buildDisplay() {

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10, 20);
  tft.setTextSize(2);
  tft.println("BME280 Sensor Data");
  tft.setCursor(10, 50);
  tft.println("Temperature: " + String(temperature) + " *C");
  tft.setCursor(10, 80);
  tft.println("Humidity: " + String(humidity) + " %");
}