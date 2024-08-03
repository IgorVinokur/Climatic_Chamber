
//Init Temperature Sensor
void bme280Init() {
  I2CBME.begin(I2C_SDA, I2C_SCL, 100000);
  bool status = bme.begin(0x76, &I2CBME);
  // You can also pass in a Wire library object like &Wire2
  // status = bme.begin(0x76, &Wire2)
  byte count = 0;
  while (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    //Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    //Serial.print("        ID of 0x60 represents a BME 280.\n");
    //Serial.print("        ID of 0x61 represents a BME 680.\n");
    delay(1000);
    if (++count > 5) break;
  } 
  if (status) Serial.println(" BME280 ... OK");
}  //bme280Init()

void encInit() {
//Encoder Settings
  enc.setBtnLevel(LOW);
  enc.setClickTimeout(500);
  enc.setDebTimeout(50);
  enc.setHoldTimeout(600);
  enc.setStepTimeout(200);
  enc.setEncReverse(0);
  enc.setEncType(EB_STEP4_LOW);
  enc.setFastTimeout(30);
  // сбросить счётчик энкодера
  enc.counter = 0;
}
void relayInit() {
  temp_relay_heating.setpoint = mydata.temp;        // установка (ставим на 40 градусов)
  temp_relay_heating.hysteresis = mydata.temp_hys;  // ширина гистерезиса
  temp_relay_heating.k = 0.5;                       // коэффициент обратной связи (подбирается по факту)
  temp_relay_cooling.setpoint = mydata.temp;        // установка (ставим на 40 градусов)
  temp_relay_cooling.hysteresis = mydata.temp_hys;  // ширина гистерезиса
  temp_relay_cooling.k = 0.5;                       // коэффициент обратной связи (подбирается по факту)
}

void bme280Read() { 
  rowtemperature = (int) bme.readTemperature();
  rowhumidity = (int) bme.readHumidity();
  temperature = rowtemperature + mydata.tempOffset;
  humidity = rowhumidity + mydata.humidityOffset;
#ifdef Debug
  Serial.print("Temperature = ");
  Serial.println(temperature);
  Serial.print("Humidity = ");
  Serial.println(humidity);
  #endif
  if (currentScreen == MAIN){
     sensorsDisplay();
  }
    //tft.println("Temp:" + String(temperature) + "*C " + "Hum:" + String(humidity) + " %" );
} //bme280Read()

void temprelay() { //Control Teperature
  if (mydata.sw_temp) {
    if (mydata.sw_tempmode) {  // If TempMode 1= Heating
      static uint32_t tempRelayTimer = 0;
      if (millis() - tempRelayTimer > 2000) {  // Set mills timer to 2 seconds
        tempRelayTimer = millis();
        temp_relay_heating.input = temperature;
        // getResult возвращает значение для управляющего устройства
        digitalWrite(RELE_TEMP, temp_relay_heating.compute(2));  // отправляем на реле. Время передаём вручную, у нас 2 секунды
      }
    } else {
      static uint32_t tempRelayTimer = 0;
      if (millis() - tempRelayTimer > 2000) {  // свой таймер на миллис, 2 секунды
        tempRelayTimer = millis();
        temp_relay_cooling.input = temperature;
        // getResult возвращает значение для управляющего устройства
        digitalWrite(RELE_TEMP, temp_relay_cooling.compute(2));  // отправляем на реле. Время передаём вручную, у нас 2 секунды
      }
    }
  }
}


