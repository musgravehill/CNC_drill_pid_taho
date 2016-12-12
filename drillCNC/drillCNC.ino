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
#define PIN_SM_SPEED A0
#define PIN_SPINDLE_SPEED A1

//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h> //Nokia 5110 LCD Displays
#include <PID_v1.h>
#include <AccelStepper.h>

//PID
double PID_setpoint_0_1023, PID_input_0_1023, PID_output_PWM; //0..1023, 0..1023, 0..255
PID PID_SPINDLE(&PID_input_0_1023, &PID_output_PWM, &PID_setpoint_0_1023, 1, 0, 0, DIRECT); 
//LCD
// Software SPI (slower updates, more flexible pin options):
Adafruit_PCD8544 LCD = Adafruit_PCD8544(PIN_LCD_CLK, PIN_LCD_DIN, PIN_LCD_DC, PIN_LCD_CE, PIN_LCD_RST);
//TIMEMACHINE
uint32_t TIMEMACHINE_prevMicros_100ms = 0L;
uint32_t TIMEMACHINE_prevMicros_500ms = 0L;
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;
//taho
volatile uint16_t TAHO_rotationCount = 0L;
uint16_t TAHO_RPM = 0L;
uint32_t TAHO_prev_ms = 0L;
//stepper motor
AccelStepper stepper_z(AccelStepper::DRIVER, PIN_SM_DRIVER_STEP, PIN_SM_DRIVER_DIR); //step, dir
int16_t SM_speed = 0; //-500 0 + 500
int8_t SM_speed_sign = 1;


void setup() {
  pinMode(PIN_TAHO_IN, INPUT);
  pinMode(PIN_SPINDLE_PWM_OUT, OUTPUT);
  pinMode(PIN_SM_DRIVER_STEP, OUTPUT);
  pinMode(PIN_SM_DRIVER_DIR, OUTPUT);
  pinMode(PIN_SM_BTN_UP, INPUT);
  pinMode(PIN_SM_BTN_SET_POS_0, INPUT);
  pinMode(PIN_SM_BTN_DOWN, INPUT);

  Serial.begin(9600);
  SM_init();
  TAHO_init();
  LCD_init();
  PID_init();
}

void loop() {
  PID_LOOP();
  TIMEMACHINE_loop();
  SM_buttons();
}
