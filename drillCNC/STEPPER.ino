void SM_init() {
  stepper_z.setMaxSpeed(350); //////////////-------------------
  stepper_z.setAcceleration(64);                            //|
}                                                           //|
                                                            //| 
void SM_SPEED_SET() {                                       //|
  SM_speed = 8 * analogRead(PIN_SM_SPEED);  //////////////----- 
  stepper_z.setSpeed(SM_speed_sign * SM_speed);
}

void SM_buttons() {
  if (digitalRead(PIN_SM_BTN_UP)) {
    SM_speed_sign = 1;
    stepper_z.runSpeed();
    return;
  }
  if (digitalRead(PIN_SM_BTN_DOWN)) {
    SM_speed_sign - 1;
    stepper_z.runSpeed();
    return;
  }
  if (digitalRead(PIN_SM_BTN_SET_POS_0)) {
    stepper_z.setCurrentPosition(0);
  }
}
