void temprelay() { //Control Teperature
  if (data.sw_temp) {
    if (data.sw_tempmode) {  // If TempMode 1= Heating
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


