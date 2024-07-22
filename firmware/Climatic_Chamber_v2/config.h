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


#include <GyverHub.h>
GyverHub hub("Climatic Chember", "ESP32S3", "");