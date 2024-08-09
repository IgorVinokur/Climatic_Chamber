void AirCirculationTimer() {
  if (mydata.sw_a_circulation) {
    // Set the period to 3 hours (3, 0, 0) and duration to 5 minutes (0, 5, 0)
    unsigned long period = timeToMillis(mydata.air_circ_Period, 0, 0);      //  Hours
    unsigned long duration = timeToMillis(0, mydata.air_circ_Duration, 0);  // Minutes
    if (!A_Circ_periodTimer.isEnabled()) {                                  // Initialize the timers if not already running
      A_Circ_periodTimer.setTimeout(period);
      A_Circ_periodTimer.start();
    }
    // Check if the period timer has elapsed
    if (A_Circ_periodTimer.isReady()) {  // Start the relay
      digitalWrite(RELE_A_CIRC, HIGH);
      #ifdef Debug
        Serial.println("Air Circulation Relay is ON");
      #endif
      A_Circ_durationTimer.setTimeout(duration);  // Start the duration timer
      A_Circ_durationTimer.start();
    }
    // Check if the duration timer has elapsed to turn off the relay
    if (A_Circ_durationTimer.isReady()) {
      digitalWrite(RELE_A_CIRC, LOW);
      #ifdef Debug
        Serial.println("Air Circulation Relay is OFF");
      #endif
    }
  }
}
void VentilationTimer() {
  if (mydata.sw_ventilation) {
    // Set the period to 3 hours (3, 0, 0) and duration to 5 minutes (0, 5, 0)
    unsigned long period = timeToMillis(mydata.venta_Period, 0, 0);      //  Hours
    unsigned long duration = timeToMillis(0, mydata.venta_Duration, 0);  // Minutes
    if (!Venta_periodTimer.isEnabled()) {                                // Initialize the timers if not already running
      Venta_periodTimer.setTimeout(period);
      Venta_periodTimer.start();
    }
    // Check if the period timer has elapsed
    if (Venta_periodTimer.isReady()) {  // Start the relay
      digitalWrite(RELE_VENTA, HIGH);
      #ifdef Debug
        Serial.println("Ventilation Relay is ON");
      #endif  
      Venta_durationTimer.setTimeout(duration);  // Start the duration timer
      Venta_durationTimer.start();
    }
    // Check if the duration timer has elapsed to turn off the relay
    if (Venta_durationTimer.isReady()) {
      digitalWrite(RELE_VENTA, LOW);
      #ifdef Debug
        Serial.println("Ventilation Relay is OFF");
      #endif
    }
  }
}
void QLampTimer() {
  if (mydata.sw_q_lamp) {
    // Set the period to 3 hours (3, 0, 0) and duration to 5 minutes (0, 5, 0)
    unsigned long period = timeToMillis(mydata.quartz_Period, 0, 0);      //  Hours
    unsigned long duration = timeToMillis(0, mydata.quartz_Duration, 0);  // Minutes
    if (!QLamp_periodTimer.isEnabled()) {                                 // Initialize the timers if not already running
      QLamp_periodTimer.setTimeout(period);
      QLamp_periodTimer.start();
    }
    // Check if the period timer has elapsed
    if (QLamp_periodTimer.isReady()) {  // Start the relay
      digitalWrite(RELE_Q_LAMP, HIGH);
      #ifdef Debug
      Serial.println("Quarz Lamp Relay is ON");
      #endif
      QLamp_durationTimer.setTimeout(duration);  // Start the duration timer
      QLamp_durationTimer.start();
    }
    // Check if the duration timer has elapsed to turn off the relay
    if (QLamp_durationTimer.isReady()) {
      digitalWrite(RELE_Q_LAMP, LOW);
      #ifdef Debug
      Serial.println("Quarz Lamp Relay is OFF");
      #endif
    }
  }
}