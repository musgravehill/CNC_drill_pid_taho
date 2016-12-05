
void PID_init() {
  PID_SPINDLE.SetMode(AUTOMATIC);
  PID_setpoint = 0;
  PID_input = 4;
}


/********************************************
   Serial Communication functions / helpers
 ********************************************/


union {                // This Data structure lets
  byte asBytes[24];    // us take the byte array
  float asFloat[6];    // sent from processing and
}                      // easily convert it to a
foo;                   // float array



// getting float values from processing into the arduino
// was no small task.  the way this program does it is
// as follows:
//  * a float takes up 4 bytes.  in processing, convert
//    the array of floats we want to send, into an array
//    of bytes.
//  * send the bytes to the arduino
//  * use a data structure known as a union to convert
//    the array of bytes back into an array of floats

//  the bytes coming from the arduino follow the following
//  format:
//  0: 0=Manual, 1=Auto, else = ? error ?
//  1: 0=Direct, 1=Reverse, else = ? error ?
//  2-5: float setpoint
//  6-9: float input
//  10-13: float output
//  14-17: float P_Param
//  18-21: float I_Param
//  22-245: float D_Param
void PID_SerialReceive()
{

  // read the bytes sent from Processing
  int index = 0;
  byte Auto_Man = -1;
  byte Direct_Reverse = -1;
  while (Serial.available() && index < 26)
  {
    if (index == 0) Auto_Man = Serial.read();
    else if (index == 1) Direct_Reverse = Serial.read();
    else foo.asBytes[index - 2] = Serial.read();
    index++;
  }

  // if the information we got was in the correct format,
  // read it into the system
  if (index == 26  && (Auto_Man == 0 || Auto_Man == 1) && (Direct_Reverse == 0 || Direct_Reverse == 1))
  {
    PID_setpoint = double(foo.asFloat[0]);
    //Input=double(foo.asFloat[1]);       // * the user has the ability to send the
    //   value of "Input"  in most cases (as
    //   in this one) this is not needed.
    if (Auto_Man == 0)                    // * only change the output if we are in
    { //   manual mode.  otherwise we'll get an
      PID_output = double(foo.asFloat[2]);    //   output blip, then the controller will
    }                                     //   overwrite.

    double p, i, d;                       // * read in and set the controller tunings
    p = double(foo.asFloat[3]);           //
    i = double(foo.asFloat[4]);           //
    d = double(foo.asFloat[5]);           //
    PID_SPINDLE.SetTunings(p, i, d);            //

    if (Auto_Man == 0) PID_SPINDLE.SetMode(MANUAL); // * set the controller mode
    else PID_SPINDLE.SetMode(AUTOMATIC);             //

    if (Direct_Reverse == 0) PID_SPINDLE.SetControllerDirection(DIRECT); // * set the controller Direction
    else PID_SPINDLE.SetControllerDirection(REVERSE);          //
  }
  Serial.flush();                         // * clear any random data from the serial buffer
}

// unlike our tiny microprocessor, the processing ap
// has no problem converting strings into floats, so
// we can just send strings.  much easier than getting
// floats from processing to here no?
void PID_SerialSend()
{
  Serial.print("PID ");
  Serial.print(PID_setpoint);
  Serial.print(" ");
  Serial.print(PID_input);
  Serial.print(" ");
  Serial.print(PID_output);
  Serial.print(" ");
  Serial.print(PID_SPINDLE.GetKp());
  Serial.print(" ");
  Serial.print(PID_SPINDLE.GetKi());
  Serial.print(" ");
  Serial.print(PID_SPINDLE.GetKd());
  Serial.print(" ");
  if (PID_SPINDLE.GetMode() == AUTOMATIC) Serial.print("Automatic");
  else Serial.print("Manual");
  Serial.print(" ");
  if (PID_SPINDLE.GetDirection() == DIRECT) Serial.println("Direct");
  else Serial.println("Reverse");
}
