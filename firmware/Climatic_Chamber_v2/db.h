#pragma once

#include <LittleFS.h>
#include <FileData.h>  // Замена епрома

struct Data {
  char apSsid[21] = AP_DEFAULT_SSID;    // Имя сети для AP режима по умолчанию
  char apPass[21] = AP_DEFAULT_PASS;    // Пароль сети для AP режима по умолчанию
  char staSsid[21] = STA_DEFAULT_SSID;  // Имя сети для STA режима по умолчанию
  char staPass[21] = STA_DEFAULT_PASS;  // Пароль сети для STA режима по умолчанию
  int gmt = 2;
  char ntp_srv[32] = "pool.ntp.org";  
  int temp = 10.0;
  int temp_hys = 0.0;
  int16_t set_humidity = 70;
  int humidity_hys = 0;
  int16_t set_draining = 80;
  int draining_hys = 0;
  bool sw_temp;
  bool sw_humidity;
  bool sw_draining;
  bool sw_a_circulation;
  bool sw_ventilation;
  bool sw_q_lamp;
  bool sw_tempmode = false;  //Temperature Relay Mode : 0=NORMAL for Cooling, and 1=REVERSE for Heatting
  bool sw_mqtt = false;
  char mqttServer[51] = "";
  char mqttUser[21] = "";
  char mqttPwd[21] = "";
  char mqttTopic[51] = "";
  int mqttPort = 1883;
  int16_t air_circ_fan_pwr = 100;
  int16_t air_circ_Period = 2;
  int16_t air_circ_Duration = 2;
  int16_t venta_Period = 2;
  int16_t venta_Duration = 2;
  int16_t quartz_Period = 2;
  int16_t quartz_Duration = 2;
  int16_t tempOffset = 0;
  int16_t humidityOffset = 0;

};

Data mydata;
FileData data(&LittleFS, "/data.dat", 'B', &mydata, sizeof(mydata));


void db_init() {

 while (!LittleFS.begin()) {  // Инициализация файловой системы
    LittleFS.format();
  }
  if (!LittleFS.begin()) Serial.println("FS Error");
  // прочитать данные из файла в переменную
  // при первом запуске в файл запишутся данные из структуры
  FDstat_t stat = data.read();

  switch (stat) {
    case FD_FS_ERR:
      Serial.println("FS Error");
      break;
    case FD_FILE_ERR:
      Serial.println("Error");
      break;
    case FD_WRITE:
      Serial.println("Data Write");
      break;
    case FD_ADD:
      Serial.println("Data Add");
      break;
    case FD_READ:
      Serial.println("Data Read");
      break;
    default:
      break;
  }

  Serial.println("Data read:");


}