#define CONNECT_TIMEOUT 10000

void startup() {
 // EEPROM.begin(eemem.blockSize());
 // eemem.begin(0, 'b');  // изменить букву в скобках на другую, чтобы восстановить настройки по умолчанию

  Serial.begin(115200);
  while (!LittleFS.begin()) {           // Инициализация файловой системы
    LittleFS.format();
  }


  if (!LittleFS.begin()) Serial.println("FS Error");


  // прочитать данные из файла в переменную
  // при первом запуске в файл запишутся данные из структуры
  FDstat_t stat = data.read();

  switch (stat) {
    case FD_FS_ERR: Serial.println("FS Error");
      break;
    case FD_FILE_ERR: Serial.println("Error");
      break;
    case FD_WRITE: Serial.println("Data Write");
      break;
    case FD_ADD: Serial.println("Data Add");
      break;
    case FD_READ: Serial.println("Data Read");
      break;
    default:
      break;
  }

  Serial.println("Data read:");


  WiFi.mode(WIFI_STA);
  Serial.println(String("Connecting ") + mydata.staSsid + ',' + mydata.staPass);
  WiFi.begin(mydata.staSsid, mydata.staPass);
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
    WiFi.softAP(mydata.apSsid, mydata.apPass);  // Create AP
    Serial.println("Fail! AP mode");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println(WiFi.localIP());
    //ClientIP = WiFi.localIP().toString().c_str();
  }

  temp_relay_heating.setpoint = mydata.temp;        // установка (ставим на 40 градусов)
  temp_relay_heating.hysteresis = mydata.temp_hys;  // ширина гистерезиса
  temp_relay_heating.k = 0.5;                          // коэффициент обратной связи (подбирается по факту)
  temp_relay_cooling.setpoint = mydata.temp;        // установка (ставим на 40 градусов)
  temp_relay_cooling.hysteresis = mydata.temp_hys;  // ширина гистерезиса
  temp_relay_cooling.k = 0.5;                          // коэффициент обратной связи (подбирается по факту)

//Display Init
  displayInit();

  //Encoder Settings
  enc.setBtnLevel(LOW);
  enc.setClickTimeout(500);
  enc.setDebTimeout(50);
  enc.setHoldTimeout(600);
  enc.setStepTimeout(200);

  enc.setEncReverse(0);
  enc.setEncType(EB_STEP4_LOW);
  enc.setFastTimeout(30);

  ui.start("cl-chamber");
  ui.attachBuild(build);
  ui.attach(action);
  ui.enableOTA();
}
