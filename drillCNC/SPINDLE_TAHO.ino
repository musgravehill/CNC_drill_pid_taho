void TAHO_init() {
  attachInterrupt(0, TAHO_interrupt, FALLING); //d2
}

void TAHO_interrupt () {
  TAHO_rotationCount++;
}

void TAHO_calc_PRM() {
  TAHO_RPM = TAHO_rotationCount * 600; //10* 100ms * countRotation  * 60 = rot per minute
  TAHO_rotationCount = 0;
  PID_input_rpm = map(TAHO_RPM, 0, 30000, 0, 1024);
}

void SPINDLE_SPEED_SET() {
  PID_setpoint_rpm = map(30 * analogRead(PIN_SPINDLE_SPEED), 0, 30000, 0, 1024);
}
