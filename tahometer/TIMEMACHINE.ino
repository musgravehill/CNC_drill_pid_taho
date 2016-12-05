void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1000ms) > 1000L) {
    TIMEMACHINE_1000ms();
    TIMEMACHINE_prevMicros_1000ms = TIMEMACHINE_currMillis;
  }
}

void TIMEMACHINE_1000ms() {
  uint16_t rpm = rpmCount * 60;
  rpmCount = 0L;
  Serial.println(rpm, DEC);
  analogWrite(11, map(rpm, 18000, 32000, 0,255)); 
}
