void TAHO_init() {
  attachInterrupt(0, TAHO_interrupt, FALLING); //d2
}

void TAHO_interrupt () {
  TAHO_rotationCount++;
}

void TAHO_calc_PRM() {
  //cli();
  uint32_t  TAHO_curr_ms = millis();  
  Serial.println(TAHO_rotationCount);  
  TAHO_RPM = TAHO_rotationCount * 15000L / (TAHO_curr_ms - TAHO_prev_ms); //rot per minute   60 000ms = 60s = 1 minute  4-holes => 60\4 = 15
  PID_input_0_1023 = map(TAHO_RPM, 0, 8300, 0, 1023);
  TAHO_rotationCount = 0L;
  TAHO_prev_ms = TAHO_curr_ms;
  //sei();
  
}

void SPINDLE_SPEED_SET() {
  PID_setpoint_0_1023 = 1020 - analogRead(PIN_SPINDLE_SPEED); //reostat inversed rotation
}
