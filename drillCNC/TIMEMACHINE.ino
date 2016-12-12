void TIMEMACHINE_loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_100ms) > 100L) {
    TIMEMACHINE_100ms();
    TIMEMACHINE_prevMicros_100ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_500ms) > 500L) {
    TIMEMACHINE_500ms();
    TIMEMACHINE_prevMicros_500ms = TIMEMACHINE_currMillis;
  }

  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_1000ms) > 1000L) {
    TIMEMACHINE_1000ms();
    TIMEMACHINE_prevMicros_1000ms = TIMEMACHINE_currMillis;
  }
}

void TIMEMACHINE_100ms() {
  TAHO_calc_PRM();
}

void TIMEMACHINE_500ms() {
  SM_SPEED_SET();
  SPINDLE_SPEED_SET();
}

void TIMEMACHINE_1000ms() {
  PID_SerialReceive(); //PID TUNE DESCTOP
  PID_SerialSend();  //PID TUNE DESCTOP
  LCD_info();
}
