#define STATIC_IP  // закомментировать если подключаетесь к мобильной точке доступа на телефоне
#define AP_DEFAULT_SSID   "Climatic Chamber"   // Стандартное имя точки доступа ESP (До 20-ти символов)
#define AP_DEFAULT_PASS   "00000000"    // Стандартный пароль точки доступа ESP (До 20-ти символов)
#define STA_DEFAULT_SSID  ""            // Стандартное имя точки доступа роутера (До 20-ти символов)
#define STA_DEFAULT_PASS  ""            // Стандартный пароль точки доступа роутера (До 20-ти символов)
#define RELE1 4
#define RELE_TEMP 5
#define RELE_THUM 6
#define RELE_DRAIN 7
#define RELE_C_VENTA 15
#define RELE_Q_LAMP 16
#define ON 0
#define OFF 1
#define I2C_SDA 48
#define I2C_SCL 47
#define SEALEVELPRESSURE_HPA (1013.25)
#define TFT_CS   10 //Display SPI
#define TFT_DC   9 //Display SPI
#define TFT_RST  8 //Display SPI
//#define TFT_SDA  11
//#define TFT_SCLK 12
#define DISPLAY_WIDTH  170 // Display Size
#define DISPLAY_HEIGHT 320 //Display Size


//#define Debug
float temperature = 0.0;
float humidity = 0.0;


//**********Libraries*****************
#include <LittleFS.h>
#include <FileData.h>       // Замена епрома
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_BME280.h>
#include <GyverNTP.h>
#include <GyverRelay.h>
#include <EncButton.h>
#include <GyverPortal.h>

//***********Objects******************
TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GyverNTP ntp(2);
GyverRelay  temp_relay_cooling(NORMAL);
GyverRelay  temp_relay_heating(REVERSE);
EncButton eb(18, 8, 3);
GyverPortal ui(&LittleFS);



struct Data {
  char apSsid[21] = AP_DEFAULT_SSID;    // Имя сети для AP режима по умолчанию
  char apPass[21] = AP_DEFAULT_PASS;    // Пароль сети для AP режима по умолчанию
  char staSsid[21] = STA_DEFAULT_SSID;  // Имя сети для STA режима по умолчанию
  char staPass[21] = STA_DEFAULT_PASS;  // Пароль сети для STA режима по умолчанию
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
Data mydata;
FileData data(&LittleFS, "/data.dat", 'B', &mydata, sizeof(mydata));


//#include <EEManager.h>  // подключаем либу
//EEManager eemem(data);  // передаём нашу переменную (фактически её адрес)
//#include <EEPROM.h>
bool mainDisplay = 0;

bool dependByTime = 1;  // флаг разрешения включения реле по времени
GPdate nowDate;
GPtime nowTime;
uint32_t startSeconds = 0;
uint32_t stopSeconds = 0;




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