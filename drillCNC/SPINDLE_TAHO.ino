void TAHO_init() {
  attachInterrupt(0, TAHO_interrupt, FALLING); //d2
}

void TAHO_interrupt () {
  TAHO_rotationCount++;
}

void TAHO_calc_PRM() {
  uint32_t  TAHO_curr_ms = millis();
  //60 000ms = 60s = 1 minute
  TAHO_RPM = TAHO_rotationCount * 60000 / (TAHO_curr_ms - TAHO_prev_ms); //rot per minute
  TAHO_rotationCount = 0;
  PID_input_rpm = map(TAHO_RPM, 0, 30000, 0, 1024);
  TAHO_prev_ms = TAHO_curr_ms;
}

void SPINDLE_SPEED_SET() {
  PID_setpoint_rpm = analogRead(PIN_SPINDLE_SPEED);
}
