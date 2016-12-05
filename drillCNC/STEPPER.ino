void SM_init() {
  stepper_z.setMaxSpeed(8192);
  stepper_z.setAcceleration(64);
  stepper_z.setSpeed(0);
}

void SM_SPEED_SET() {
  SM_speed = 8 * analogRead(PIN_SM_SPEED);
  stepper_z.setSpeed(SM_speed);
}

void SM_buttons() {
  if (digitalRead(PIN_SM_BTN_UP)) {
    //stepper_z.setSpeed(SM_speed); //setSpeed in SM_SPEED_SET()
    stepper_z.runSpeed();
    return;
  }
  if (digitalRead(PIN_SM_BTN_DOWN)) {
    //stepper_z.setSpeed(-1 * SM_speed); //setSpeed in SM_SPEED_SET()
    stepper_z.runSpeed();
    return;
  }
  if (digitalRead(PIN_SM_BTN_SET_POS_0)) {
    stepper_z.setCurrentPosition(0);
  }
}
