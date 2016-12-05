
uint32_t TIMEMACHINE_prevMicros_1000ms = 0L;
//volatile  uint32_t  lastTimePulse = 0L; 
volatile uint16_t rpmCount = 0L;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, interrupt_RPM, FALLING); //d2
  
}

void loop() {
  TIMEMACHINE_loop();
}

void interrupt_RPM () {
  rpmCount++;
  //lastTimePulse = micros();
}
