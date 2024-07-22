#pragma once
#include <GyverDBFile.h>
#include <LittleFS.h>
GyverDBFile db(&LittleFS, "data.db");

enum dbid : size_t {
    apSsid,
    apPass,
    staSsid,
    staPass,
    gmt,
    set_temp,
    temp_hys,
    set_humidity,
    humidity_hys,
    set_drainage,
    drainage_hys,
    sw_temp,
    sw_humidity,
    sw_drainage,
    sw_a_circulation,
    sw_ventilation,
    sw_q_lamp,
    sw_tempmode,
    sw_mqtt,
    mqttServer,
    mqttUser,
    mqttPwd,
    mqttTopic,
    mqttPort,
    air_circ_fan_pwr,
    air_circ_Period,
    air_circ_Duration,
    venta_Period,
    venta_Duration,
    quartz_Period,
    quartz_Duration,
    tempOffset,
    humidityOffset,
};

void db_init() {
    LittleFS.begin();
    db.begin();
    db.init(dbid::apSsid, AP_DEFAULT_SSID);
    db.init(dbid::apPass, AP_DEFAULT_PASS);
    db.init(dbid::staSsid, STA_DEFAULT_SSID);
    db.init(dbid::staPass, STA_DEFAULT_PASS);
    db.init(dbid::gmt, 2);
    db.init(dbid::set_temp, 10);
    db.init(dbid::temp_hys, 0);
    db.init(dbid::set_humidity, 70);
    db.init(dbid::humidity_hys, 0);
    db.init(dbid::set_drainage, 80);
    db.init(dbid::drainage_hys, "");
    db.init(dbid::sw_humidity, "");
    db.init(dbid::sw_drainage, "");
    db.init(dbid::sw_a_circulation, "");
    db.init(dbid::sw_ventilation, "");
    db.init(dbid::sw_q_lamp, "");
    db.init(dbid::sw_tempmode, false);
    db.init(dbid::sw_mqtt, false);
    db.init(dbid::mqttServer, "");
    db.init(dbid::mqttUser, "");
    db.init(dbid::mqttPwd, "");
    db.init(dbid::mqttTopic, "");
    db.init(dbid::mqttPort, 1883);
    db.init(dbid::air_circ_fan_pwr, 100);
    db.init(dbid::air_circ_Period, 2);
    db.init(dbid::air_circ_Duration, 2);
    db.init(dbid::venta_Period, 2);
    db.init(dbid::venta_Duration, 2);
    db.init(dbid::quartz_Period, 2);
    db.init(dbid::quartz_Duration, 2);
    db.init(dbid::tempOffset, 0);
    db.init(dbid::humidityOffset, 0);
}

