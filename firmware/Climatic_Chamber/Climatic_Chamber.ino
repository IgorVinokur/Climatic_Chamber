#include "data.h"

void setup() {

  startup();

  bme280Init();
  //EEPROM.begin(100);     // выделить память (больше или равно размеру структуры данных)
  //eemem.begin(0, 'e');  // изменить букву в скобках на другую, чтобы восстановить настройки по умолчанию


  pinMode(RELE_TEMP, OUTPUT);
  pinMode(RELE_THUM, OUTPUT);
  pinMode(RELE_DRAIN, OUTPUT);
  pinMode(RELE_C_VENTA, OUTPUT);
  pinMode(RELE_Q_LAMP, OUTPUT);

  // if (data.rele_1_isOn) digitalWrite(RELE1, ON);
  // else digitalWrite(RELE1, OFF);
  // digitalWrite(RELE2, OFF);

}  //setup()


void loop() {
  // eemem.tick();
  data.tick();
  ui.tick();
  ntp.tick();
  enc.tick();
  temprelay();


displayMenu();

  // раз в 1 сек делаем дела
  static uint32_t ms1 = 0;
  if (millis() - ms1 >= 1000) {
    ms1 = millis();

    bme280Read();

    // отдаем текущую дату и время переменным в веб интерфейс
    nowTime.set(ntp.hour(), ntp.minute(), ntp.second());
    nowDate.set(ntp.year(), ntp.month(), ntp.day());
    // если разрешено, включаем по времени нагрузку ( свет или насос)
    if (currentScreen == MAIN) {
      if (ntp.synced()) {
        clockDisplay();

      }  //Serial.println(ntp.timeString());
    }
  }

 
}  //loop()
