void TAHO_init() {
  attachInterrupt(0, TAHO_interrupt, FALLING); //d2
}

void TAHO_interrupt () {
  TAHO_rotationCount++;
}

void TAHO_calc_PRM() {
  TAHO_RPM = TAHO_rotationCount * 60;
  TAHO_rotationCount = 0;
}
