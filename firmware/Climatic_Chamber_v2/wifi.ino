
void wifi_Init() {
  // ======= AP =======
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(db[dbid::apSsid], db[dbid::apPass]);
  Serial.println(db[dbid::apSsid]);
  Serial.println("IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println();

  // ======= STA =======
  bool wifi_ok = false;

  if (db[dbid::staSsid].length()) {
    Serial.println("Connecting " + (db[dbid::staSsid]) + ',' + (db[dbid::staPass]));
    WiFi.begin(db[dbid::staSsid], db[dbid::staPass]);
    wifi_ok = true;
    Serial.println("Connecting");
    int tries = 20;
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println('.');
      if (!--tries) {
        wifi_ok = false;
        break;
      }
    }
    Serial.println();
    Serial.println("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("STA not configured");
  }
  Serial.println();

  if (!wifi_ok) return;
}