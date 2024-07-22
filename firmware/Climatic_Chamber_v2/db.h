#pragma once
#include <GyverDBFile.h>
#include <LittleFS.h>
GyverDBFile db(&LittleFS, "settings.db");

enum dbid : size_t {
    apSsid,
    apPass,
    staSsid,
    staPass,
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
    fan_pwr,
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
    db.init(dbid::apSsid, "");
    db.init(dbid::apPass, "");
    db.init(dbid::staSsid, "");
    db.init(dbid::staPass, "");
    db.init(dbid::set_temp, "");
    db.init(dbid::temp_hys, "");
    db.init(dbid::set_humidity, 0);
    db.init(dbid::humidity_hys, 0);
    db.init(dbid::set_drainage, 60);
    db.init(dbid::drainage_hys, "");
    db.init(dbid::sw_humidity, "");
    db.init(dbid::sw_drainage, "");
    db.init(dbid::sw_a_circulation, "");
    db.init(dbid::sw_ventilation, "");
    db.init(dbid::sw_q_lamp, "");
    db.init(dbid::sw_tempmode, "");
    db.init(dbid::sw_mqtt, "");
    db.init(dbid::mqttServer, "");
    db.init(dbid::mqttUser, "");
    db.init(dbid::mqttPwd, "");
    db.init(dbid::mqttTopic, "");
    db.init(dbid::mqttPort, "");
    db.init(dbid::fan_pwr, "");
    db.init(dbid::air_circ_Period, "");
    db.init(dbid::air_circ_Duration, "");
    db.init(dbid::venta_Period, "");
    db.init(dbid::venta_Duration, "");
    db.init(dbid::quartz_Period, "");
    db.init(dbid::quartz_Duration, "");
    db.init(dbid::tempOffset, "");
    db.init(dbid::humidityOffset, "");
}

