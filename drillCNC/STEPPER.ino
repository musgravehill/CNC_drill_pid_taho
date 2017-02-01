//I use 1\16 microstepping  m0=gnd m1=gnd m2=+5V

void SM_init() {
  stepper_z.setMaxSpeed(8000); 
  stepper_z.setAcceleration(0);                            
}                                                           

void SM_SPEED_SET() {                                      
  SM_speed = map(analogRead(PIN_SM_SPEED), 0, 1023, 0, 8000);  
  stepper_z.setSpeed(SM_speed_sign * SM_speed);
}
void SM_buttons() {
  if (!digitalRead(PIN_SM_BTN_UP)) {
    SM_speed_sign = 1;
    SM_SPEED_SET();
    stepper_z.runSpeed();
    return;
  }
  if (!digitalRead(PIN_SM_BTN_DOWN)) {
    SM_speed_sign= - 1;
    SM_SPEED_SET();
    stepper_z.runSpeed();
    return;
  }
  if (!digitalRead(PIN_SM_BTN_SET_POS_0)) {
    stepper_z.setCurrentPosition(0);
  }
}
float SM_get_Z_offset_mm() {
  return stepper_z.currentPosition() * 0.00078125; //offset by 1 microstep 
}

