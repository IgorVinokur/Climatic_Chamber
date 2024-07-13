#define STATIC_IP                           // закомментировать если подключаетесь к мобильной точке доступа на телефоне
#define AP_DEFAULT_SSID "Climatic Chamber"  // Стандартное имя точки доступа ESP (До 20-ти символов)
#define AP_DEFAULT_PASS "00000000"          // Стандартный пароль точки доступа ESP (До 20-ти символов)
#define STA_DEFAULT_SSID ""                 // Стандартное имя точки доступа роутера (До 20-ти символов)
#define STA_DEFAULT_PASS ""                 // Стандартный пароль точки доступа роутера (До 20-ти символов)
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
#define TFT_CS 10  //Display SPI
#define TFT_DC 9   //Display SPI
#define TFT_RST 8  //Display SPI
//#define TFT_SDA  11
//#define TFT_SCLK 12
#define ENCODER_PIN_A 40
#define ENCODER_PIN_B 41
#define ENCODER_PIN_SW 42

#define DISPLAY_WIDTH 170   // Display Size
#define DISPLAY_HEIGHT 320  //Display Size


//#define Debug
int16_t rowtemperature;  //temperature from sensor
int16_t rowhumidity;     //humidity from sensor
int16_t temperature;     //calibrated temperature
int16_t humidity;        //calibrated humidity


//**********Libraries*****************
#include <LittleFS.h>
#include <FileData.h>  // Замена епрома
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <Adafruit_BME280.h>
#include <GyverNTP.h>
#include <GyverRelay.h>
#include <EncButton.h>
#include <GyverPortal.h>
#include <PubSubClient.h>

//***********Objects******************
TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
GyverNTP ntp(2);
GyverRelay temp_relay_cooling(NORMAL);
GyverRelay temp_relay_heating(REVERSE);
EncButton enc(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SW);
GyverPortal ui(&LittleFS);
WiFiClient espClient;
PubSubClient client(espClient);


struct Data {
  char apSsid[21] = AP_DEFAULT_SSID;    // Имя сети для AP режима по умолчанию
  char apPass[21] = AP_DEFAULT_PASS;    // Пароль сети для AP режима по умолчанию
  char staSsid[21] = STA_DEFAULT_SSID;  // Имя сети для STA режима по умолчанию
  char staPass[21] = STA_DEFAULT_PASS;  // Пароль сети для STA режима по умолчанию
  int gmt = 2;
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
  int16_t air_circulation_fan_pwr = 100;
  int16_t air_circulation_Period = 2;
  int16_t air_circulation_Duration = 2;
  int16_t venta_Hours = 2;
  int16_t venta_work_time = 2;
  int16_t quartz_Hours = 2;
  int16_t quartz_work_time = 2;
  int16_t tempOffset = 0.0;
  int16_t humidityOffset = 0;

  bool dependbyTempr;
  bool rele_1_isOn = 0;
  GPtime startTime;
  GPtime stopTime;
  int16_t minTempr = 0;
  int16_t maxTempr = 0;
};

//#include <EEManager.h>  // подключаем либу
//EEManager eemem(data);  // передаём нашу переменную (фактически её адрес)
//#include <EEPROM.h>

Data mydata;
FileData data(&LittleFS, "/data.dat", 'B', &mydata, sizeof(mydata));

//*****Display Variables ******************
enum Screen { MAIN,
              MENU,
              CONFIGURATION,
              SETUP,
              INFO,
              TEMP_OFFSET,
              HUMIDITY_OFFSET,
              TEMP_CONTROL,
              HUM_CONTROL,
              DRAIN_CONTROL,
              A_CIRCUL_CONTROL };
Screen currentScreen = MAIN;
bool mainDisplay = 0;
int selectedMenuItem = 0;
int selectedSubMenuItem = 0;
int selectedTempControlItem = 0;
int selectedHumControlItem = 0;
int selectedDrainControlItem = 0;
int selectedACirculControlItem = 0;
int topMenuItem = 0;
int topSubMenuItem = 0;
int position = 0;
const int itemsPerPage = 4;
unsigned long lastInteractionTime = 0;
const unsigned long timeoutDuration = 30000;  //Menu unuse Timeout  30 seconds
//****** End Display Variables*******




//time_t previusTimestring;

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

const uint8_t wireless[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0,
  0x00, 0x07, 0xfe, 0x00, 0x1e, 0x8f, 0x80, 0x38,
  0x01, 0xe0, 0xe1, 0xf8, 0x70, 0xc7, 0xfe, 0x20,
  0x0e, 0x07, 0x00, 0x1c, 0x01, 0x80, 0x11, 0xf8,
  0x80, 0x03, 0xbc, 0x00, 0x06, 0x06, 0x00, 0x02,
  0x44, 0x00, 0x00, 0xf0, 0x00, 0x00, 0xf0, 0x00,
  0x00, 0xf0, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

const uint8_t nowireless[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00,
                                       0x70, 0x07, 0xff, 0xe0, 0x1f, 0x0f, 0x80, 0x38,
                                       0x07, 0xc0, 0xe1, 0xfe, 0x70, 0xc7, 0xfe, 0x30,
                                       0x0e, 0x7f, 0x00, 0x18, 0xe1, 0x80, 0x13, 0xf8,
                                       0x80, 0x07, 0xfc, 0x00, 0x0f, 0x06, 0x00, 0x1c,
                                       0x60, 0x00, 0x78, 0xf0, 0x00, 0xe0, 0xf0, 0x00,
                                       0xc0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                       0x00, 0x00, 0x00, 0x00 };

const uint8_t cloud[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x06, 0x38, 0x00,
                                  0x00, 0x0c, 0x18, 0x00, 0x00, 0xf8, 0x0c, 0x00, 0x03, 0xf8, 0x0c, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x06, 0x00, 0x0f, 0x00, 0x06, 0x00, 0x01, 0x80,
                                  0x06, 0x00, 0x01, 0x80, 0x02, 0x00, 0x01, 0x80, 0x03, 0x00, 0x01, 0x80, 0x01, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const uint8_t nocloud[] PROGMEM = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0xc0, 0x80, 0x00, 0x00, 0xe3, 0xf0, 0x00, 0x00, 0x76, 0x38, 0x00,
                                    0x00, 0x38, 0x18, 0x00, 0x00, 0xdc, 0x0c, 0x00, 0x03, 0xce, 0x0c, 0x00, 0x03, 0x07, 0x0e, 0x00, 0x06, 0x03, 0x8f, 0x00, 0x06, 0x01, 0xc1, 0x80,
                                    0x06, 0x00, 0xe1, 0x80, 0x02, 0x00, 0x71, 0x80, 0x03, 0x00, 0x39, 0x80, 0x01, 0xff, 0xdd, 0x00, 0x00, 0x7f, 0xee, 0x00, 0x00, 0x00, 0x06, 0x00,
                                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };