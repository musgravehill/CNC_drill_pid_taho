///////////////////////

//!2 TAHO IN
//!3 SPINDLE PWM OUT works on pins 3 5bug 6bug 9 10 11
//4 SM DRIVER DIR
//5 SM BTN DOWN
//6 SM DRIVER STEP
//7 SM BTN SET POS 0
//8 SM BTN UP
//9  LCD RST   перезагрузки контроллера дисплея.
//10 LCD CE    разрешает или запрещает ввод данных в контроллер дисплея
//11 LCD DC    режима ввода данных - Данные/Команды
//12 LCD DIN   Вход данных SPI
//13 LCD CLK   Тактирующий SPI

#include <AccelStepper.h>

AccelStepper stepper_z(AccelStepper::DRIVER, 2, 3); //step, dir









//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_223ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;
//taho
volatile uint16_t TAHO_rotationCount = 0L;
//stepper motor
int16_t SM_speedPrev = 0; //-500 0 + 500

void setup() {
  SM_init();
}

void loop() {
  if (digitalRead(4)) {
    stepper_z.runSpeed();
  }

  uint32_t  TIMEMACHINE_currMillis = millis();
  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_223ms) > 223L) {
    int sensorValue = analogRead(A1);
    int speed_new = 8 * sensorValue;
    if (abs(speed_prev - speed_new) > 32 ) {
      stepper_z.setSpeed(speed_new);
      speed_prev = speed_new;
    }
    TIMEMACHINE_prevMicros_223ms = TIMEMACHINE_currMillis;
  }
}
