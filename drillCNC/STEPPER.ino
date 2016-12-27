void SM_init() {
  stepper_z.setMaxSpeed(350); //////////////-------------------
  stepper_z.setAcceleration(64);                            //|
}                                                           //|
//|
void SM_SPEED_SET() {                                       //|
  SM_speed = map(analogRead(PIN_SM_SPEED), 0, 1023, 0, 100);  //////////////-----
  stepper_z.setSpeed(SM_speed_sign * SM_speed);
}

void SM_buttons() {
  if (!digitalRead(PIN_SM_BTN_UP)) {
    SM_speed_sign = 1;
    stepper_z.runSpeed();
    return;
  }
  if (!digitalRead(PIN_SM_BTN_DOWN)) {
    SM_speed_sign= - 1;
    stepper_z.runSpeed();
    return;
  }
  if (!digitalRead(PIN_SM_BTN_SET_POS_0)) {
    stepper_z.setCurrentPosition(0);
  }
}

float SM_get_Z_offset_mm() {
  return stepper_z.currentPosition() * 0.001; //  steps for 1 rotation => offset by screw 2..4 mm for 1 rotation
}

