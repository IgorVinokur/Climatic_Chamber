#define CONNECT_TIMEOUT 10000


void startup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  Serial.println("Connecting " + (db[dbid::staSsid]) + ',' + (db[dbid::staPass]));
  WiFi.begin(db[dbid::staSsid], db[dbid::staPass]);
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
    WiFi.softAP(db[dbid::apSsid], db[dbid::apPass]);  // Create AP
    Serial.println("Fail! AP mode");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println(WiFi.localIP());
    //ClientIP = WiFi.localIP().toString().c_str();
  }
}
