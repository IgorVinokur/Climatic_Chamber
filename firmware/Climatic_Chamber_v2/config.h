#pragma once

//#define Debug
#define STATIC_IP                           // закомментировать если подключаетесь к мобильной точке доступа на телефоне
#define AP_DEFAULT_SSID "Climatic Chamber"  // Стандартное имя точки доступа ESP (До 20-ти символов)
#define AP_DEFAULT_PASS "00000000"          // Стандартный пароль точки доступа ESP (До 20-ти символов)
#define STA_DEFAULT_SSID ""                 // Стандартное имя точки доступа роутера (До 20-ти символов)
#define STA_DEFAULT_PASS ""                 // Стандартный пароль точки доступа роутера (До 20-ти символов)
#define CONNECT_TIMEOUT 10000               //WiFI Connection Timeout
#define RELE1 4
#define I2C_SDA 48
#define I2C_SCL 47
#define SEALEVELPRESSURE_HPA (1013.25)
#define RELE_TEMP 5 //Temperature Relay
#define RELE_HUM 6  //Humidity Relay
#define RELE_DRAIN 7 // Drain Relay
#define RELE_A_CIRC 15 // Air Circulation Relay
#define RELE_VENTA 16 // Venta Relay
#define RELE_Q_LAMP 17 // Q Lamp Relay
#define ENCODER_PIN_A 40  //Encoder A
#define ENCODER_PIN_B 41  // Encoder B
#define ENCODER_PIN_SW 42 //Encoder SW
#define TFT_CS 10  //Display SPI
#define TFT_DC 9   //Display SPI
#define TFT_RST 8  //Display SPI
//#define TFT_SDA  11
//#define TFT_SCLK 12
#define DISPLAY_WIDTH 170   // Display Size
#define DISPLAY_HEIGHT 320  //Display Size
#define ON 0
#define OFF 1

#include <Wire.h>
#include <Adafruit_BME280.h>
TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme;

#include <GyverRelay.h>
GyverRelay temp_relay_cooling(NORMAL); //Cooling Relay
GyverRelay temp_relay_heating(REVERSE); //Heating Relay
GyverRelay hum_relay(REVERSE); // Humidity Relay

#include <EncButton.h>
EncButton enc(ENCODER_PIN_A, ENCODER_PIN_B, ENCODER_PIN_SW);

#include <GyverTimer.h>
GTimer A_Circ_periodTimer;
GTimer A_Circ_durationTimer;
GTimer Venta_periodTimer;
GTimer Venta_durationTimer;
GTimer QLamp_periodTimer;
GTimer QLamp_durationTimer;

#include <Adafruit_Sensor.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

char formattedDate[9]; // "HH:MM:SS" format
int16_t rowtemperature;  //temperature from sensor
int16_t rowhumidity;     //humidity from sensor
int16_t temperature;     //calibrated temperature
int16_t humidity;        //calibrated humidity

// Function to convert hours, minutes, and seconds to milliseconds
unsigned long timeToMillis(int hours, int minutes, int seconds) {
  return (unsigned long)hours * 3600000UL + (unsigned long)minutes * 60000UL + (unsigned long)seconds * 1000UL;
}

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
              A_CIRCUL_CONTROL,
              VENTA_CONTROL,
              QUARTZ_CONTROL };
Screen currentScreen = MAIN;
bool mainDisplay = 0;
int selectedMenuItem = 0;
int selectedSubMenuItem = 0;
int selectedTempControlItem = 0;
int selectedHumControlItem = 0;
int selectedDrainControlItem = 0;
int selectedACirculControlItem = 0;
int selectedVentaControlItem = 0;
int selectedQuartzControlItem = 0;
int topMenuItem = 0;
int topSubMenuItem = 0;
int position = 0;
const int itemsPerPage = 4;
unsigned long lastInteractionTime = 0;
const unsigned long timeoutDuration = 30000;  //Menu unuse Timeout  30 seconds
//****** End Display Variables*******


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












