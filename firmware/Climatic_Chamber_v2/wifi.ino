
void wifi_Init() {

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
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(mydata.apSsid, mydata.apPass);  // Create AP
    Serial.println("Fail! AP mode");
    Serial.println(WiFi.softAPIP());
  } else {
    Serial.println(WiFi.localIP());
    //ClientIP = WiFi.localIP().toString().c_str();
  }

}