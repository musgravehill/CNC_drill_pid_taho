#include <AccelStepper.h>

AccelStepper stepper1(AccelStepper::DRIVER, 2, 3); //step, dir
//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_223ms = 1L;
int speed_prev = 0;

void setup() {
  stepper1.setMaxSpeed(8192);
  stepper1.setAcceleration(64);
  //stepper1.moveTo(200);
}

void loop() {
  if (digitalRead(4)) {
    stepper1.runSpeed();
  }

  //stepper1.run();
  uint32_t  TIMEMACHINE_currMillis = millis();
  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_223ms) > 223L) {
    int sensorValue = analogRead(A1);
    int speed_new = 8 * sensorValue;
    if (abs(speed_prev - speed_new) > 32 ) {
      stepper1.setSpeed(speed_new);
      speed_prev = speed_new;
    }
    TIMEMACHINE_prevMicros_223ms = TIMEMACHINE_currMillis;
  }
}
