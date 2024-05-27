#define CONNECT_TIMEOUT 10000

void startup() {
  EEPROM.begin(eemem.blockSize());
  eemem.begin(0, 'b');  // изменить букву в скобках на другую, чтобы восстановить настройки по умолчанию

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println(String("Connecting ") + data.ssid + ',' + data.pass);
  WiFi.begin(data.ssid, data.pass);
  uint32_t tmr = millis();
  bool fail = false;
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - tmr >= CONNECT_TIMEOUT) {
      fail = 1;
      break;
    }
    Serial.print(".");
    delay(500);
  }

  if (fail) {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(data.AP_ssid);
    Serial.println("Fail! AP mode");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println(WiFi.localIP());
    //ClientIP = WiFi.localIP().toString().c_str();
  }

  temp_relay_heating.setpoint = data.temp;        // установка (ставим на 40 градусов)
  temp_relay_heating.hysteresis = data.temp_hys;  // ширина гистерезиса
  temp_relay_heating.k = 0.5;                          // коэффициент обратной связи (подбирается по факту)

  temp_relay_cooling.setpoint = data.temp;        // установка (ставим на 40 градусов)
  temp_relay_cooling.hysteresis = data.temp_hys;  // ширина гистерезиса
  temp_relay_cooling.k = 0.5;                          // коэффициент обратной связи (подбирается по факту)



  //Encoder Settings
  eb.setBtnLevel(LOW);
  eb.setClickTimeout(500);
  eb.setDebTimeout(50);
  eb.setHoldTimeout(600);
  eb.setStepTimeout(200);

  eb.setEncReverse(0);
  eb.setEncType(EB_STEP4_LOW);
  eb.setFastTimeout(30);

  ui.start("cl-chamber");
  ui.attachBuild(build);
  ui.attach(action);
  ui.enableOTA();
}
