#define STATIC_IP  // закомментировать если подключаетесь к мобильной точке доступа на телефоне
#define RELE1 14
#define RELE_TEMP 9
#define RELE_THUM 10
#define RELE_DRAIN 11
#define RELE_C_VENTA 12
#define RELE_Q_LAMP 13
#define ON 0
#define OFF 1
#define SEALEVELPRESSURE_HPA (1013.25)




#include <GyverNTP.h>
GyverNTP ntp(2);

#include <GyverRelay.h>
GyverRelay  temp_relay_cooling(NORMAL);
GyverRelay  temp_relay_heating(REVERSE);

#include <EncButton.h>
EncButton eb(18, 8, 3);


#include <LittleFS.h>

#include <GyverPortal.h>
GyverPortal ui(&LittleFS);

#include <Wire.h>
#include <Adafruit_BME280.h>  // для датчика BME280
Adafruit_BME280 bme;          // I2C

struct Data {
  char ssid[20] = "";
  char pass[20] = "";
  char AP_ssid[20] = "";
  int gmt = 2;
  float temp = 10.0;
  float temp_hys = 0.0;
  int16_t humidity = 70;
  int humidity_hys = 0;
  int16_t drainage = 70;
  int drainage_hys = 0;
  bool sw_temp;
  bool sw_humidity;
  bool sw_drainage;
  bool sw_a_circulation;
  bool sw_ventilation;
  bool sw_q_lamp;
  bool sw_tempmode = false;  //Temperature Relay Mode : 0=NORMAL for Cooling, and 1=REVERSE for Heatting
  float fan_pwr = 100;
  int16_t air_circulation_Hours = 2;
  int16_t circulation_work_time = 2;
  int16_t venta_Hours = 2;
  int16_t venta_work_time = 2;
  int16_t quartz_Hours = 2;
  int16_t quartz_work_time = 2;
  float tempOffset = 0.0;
  int16_t humidityOffset = 0;
  
  bool dependbyTempr;
  bool rele_1_isOn = 0;
  GPtime startTime;
  GPtime stopTime;
  int16_t minTempr = 0;
  int16_t maxTempr = 0;
  
};
Data data;

#include <EEManager.h>  // подключаем либу
EEManager eemem(data);  // передаём нашу переменную (фактически её адрес)
//#include <EEPROM.h>

 bool dependByTime = 1;  // флаг разрешения включения реле по времени
GPdate nowDate;
GPtime nowTime;
uint32_t startSeconds = 0;
uint32_t stopSeconds = 0;
float temperature = 0.0;
float humidity = 0.0;


//Set Static IP**********************************************
#ifdef STATIC_IP
//со статическим айпишничком
IPAddress staticIP(192, 168, 1, 201);  // важно правильно указать третье число - подсеть, смотри пояснения выше
IPAddress gateway(192, 168, 1, 1);     // и тут изменить тройку на свою подсеть
IPAddress subnet(255, 255, 255, 0);
IPAddress dns1(192, 168, 1, 1);  // изменить тройку на свою подсеть
IPAddress dns2(8, 8, 8, 8);
#endif
//**************************************************************