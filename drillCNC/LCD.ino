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

  LCD.setCursor(0, 0);
  LCD.setTextSize(1);
  LCD.println("Z-offset mm");
  LCD.setTextSize(2);
  LCD.println(SM_get_Z_offset_mm(), 2);

  LCD.drawLine(0, 24, 83, 24, BLACK);

  LCD.setCursor(0, 26);
  LCD.setTextSize(1);
  LCD.println("Spindle RPM");
  LCD.setTextSize(2);
  LCD.println(TAHO_RPM, DEC);

  LCD.display();
}


