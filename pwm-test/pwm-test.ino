int pwmPin = 3;
uint32_t TIMEMACHINE_prevMicros_99ms = 1L;

void setup() {

}

void loop() {
  uint32_t  TIMEMACHINE_currMillis = millis();
  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_99ms) > 99L) {
    int sensorValue = analogRead(A0);
    int pwmValue = map(sensorValue, 0, 1023, 0, 255);
    analogWrite(pwmPin, pwmValue);
    TIMEMACHINE_prevMicros_99ms = TIMEMACHINE_currMillis;
  }
}


