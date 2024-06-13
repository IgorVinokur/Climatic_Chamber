//запускаем датчик температуры
void bme280Init() {
  I2CBME.begin(I2C_SDA, I2C_SCL, 100000);
  bool status = bme.begin(0x76, &I2CBME); 
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  } else Serial.println(" BME280 ... OK");
}  //bme280Init()

// считываем температуру, влажность
void bme280Read() {
  float previusTemp;
  float previusHum;
  rowtemperature = (int) bme.readTemperature();
  rowhumidity = (int) bme.readHumidity();
  temperature = rowtemperature + mydata.tempOffset;
  humidity = rowhumidity + mydata.humidityOffset;
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  #ifdef Debug
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  //    Serial.print("Pressure = ");
  //    Serial.print(bme.readPressure() / 100.0F);
  //    Serial.println(" hPa");
  //    Serial.print("Approx. Altitude = ");
  //    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  //    Serial.println(" m");
  #endif

  if (mainDisplay){
    
    tft.setTextColor(ST77XX_BLACK);
    tft.setCursor(235, 72);
    tft.setTextSize(3);
    //tft.printf("%.2fC", previusTemp);
    tft.println(String(previusTemp));
    tft.setCursor(240, 140);
    //tft.printf("%.1f%%", previusHum);
    tft.println(String(previusHum));
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(3);
    tft.setCursor(230, 35);
    tft.println("Temp");
    tft.setCursor(235, 72);
    //tft.printf("%.2fC", temperature);
    //tft.setTextSize(2);
    previusTemp = temperature;
    previusHum = humidity;
    tft.println(String(temperature) + "C");
    tft.setCursor(235, 110);
    tft.setTextSize(3);
    tft.println("Hum");
    tft.setCursor(240, 140);
    //tft.printf("%.1f%%", humidity);
    //tft.setTextSize(3);
    tft.println(String(humidity) + "%");
    

  }
    //tft.println("Temp:" + String(temperature) + "*C " + "Hum:" + String(humidity) + " %" );
} //bme280Read()