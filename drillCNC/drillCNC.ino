///////////////////////

#define PIN_TAHO_IN 2 //!2 Interrupt 
#define PIN_SPINDLE_PWM_OUT 3//SPINDLE PWM OUT works on pins 3 5bug 6bug 9 10 11
#define PIN_SM_DRIVER_STEP 4
#define PIN_SM_DRIVER_DIR 5
#define PIN_SM_BTN_UP 6
#define PIN_SM_BTN_SET_POS_0 7
#define PIN_SM_BTN_DOWN 8
#define PIN_LCD_RST 9 //перезагрузки контроллера дисплея.
#define PIN_LCD_CE  10 //разрешает или запрещает ввод данных в контроллер дисплея
#define PIN_LCD_DC 11 //режима ввода данных - Данные/Команды
#define PIN_LCD_DIN 12 //Вход данных SPI
#define PIN_LCD_CLK 13 //Тактирующий SPI

//A0 SM SPEED
//A1 SPINDLE SPEED

//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> //Nokia 5110 LCD Displays

#include <AccelStepper.h>

//LCD
// Software SPI (slower updates, more flexible pin options):
Adafruit_PCD8544 LCD = Adafruit_PCD8544(PIN_LCD_CLK, PIN_LCD_DIN, PIN_LCD_DC, PIN_LCD_CE, PIN_LCD_RST);

//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_223ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;
//taho
volatile uint16_t TAHO_rotationCount = 0L;
uint16_t TAHO_RPM = 0L;
//stepper motor
AccelStepper stepper_z(AccelStepper::DRIVER, 2, 3); //step, dir
int16_t SM_speedPrev = 0; //-500 0 + 500

void setup() {
  Serial.begin(9600);
  SM_init();
  TAHO_init();
  LCD_init();
}

void loop() {
  if (digitalRead(4)) {
    stepper_z.runSpeed();
  }

  uint32_t  TIMEMACHINE_currMillis = millis();
  if ((TIMEMACHINE_currMillis - TIMEMACHINE_prevMicros_223ms) > 223L) {
    int sensorValue = analogRead(A1);
    int speed_new = 8 * sensorValue;
    if (abs(SM_speedPrev - speed_new) > 32 ) {
      stepper_z.setSpeed(speed_new);
      SM_speedPrev = speed_new;
    }
    TIMEMACHINE_prevMicros_223ms = TIMEMACHINE_currMillis;
  }
}
