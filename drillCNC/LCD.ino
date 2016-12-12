void LCD_init() {
  LCD.begin();
  LCD.setContrast(60);
  LCD.clearDisplay();
  LCD.setTextColor(BLACK);
  //tests
  LCD.fillRect(0, 0, 84, 48, BLACK);
  LCD.display();
  delay(1);
}

void LCD_info() {
  LCD.clearDisplay();
  LCD.setTextSize(2);  
  LCD.setCursor(0, 0);
  LCD.println(SM_speed, DEC);
  LCD.println(TAHO_RPM, DEC);
  LCD.println(PID_output_PWM, DEC);

  LCD.setTextSize(1);  
  LCD.setCursor(66, 3);
  LCD.println("mm");

  LCD.setCursor(66, 19);
  LCD.println("rpm");

  
  LCD.display();
}


