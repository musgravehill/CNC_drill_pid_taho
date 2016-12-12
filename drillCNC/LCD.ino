void LCD_init() {
  LCD.begin();
  LCD.setContrast(60);
  LCD.clearDisplay();
  LCD.setTextColor(BLACK);
  //tests
  LCD.fillRect(0, 0, 84, 48, BLACK);
  LCD.display();
  delay(1);

  LCD.clearDisplay();
  LCD.setCursor(0, 0);
  LCD.setTextSize(1);
  LCD.println("Z-offset mm");
  LCD.drawLine(0, 24, 83, 24, BLACK);
  LCD.setCursor(0, 26);
  LCD.println("Spindle RPM");
}

void LCD_info_z_axis_mm() {
  LCD.fillRect(0, 8, 84, 15, WHITE);
  LCD.setCursor(0, 8);
  LCD.setTextSize(2);
  LCD.println(SM_get_Z_offset_mm(), 2);
  LCD.display();
}

void LCD_info_rpm() {
  LCD.fillRect(0, 35, 84, 48, WHITE);
  LCD.setCursor(0, 35);
  LCD.setTextSize(2);
  LCD.println(TAHO_RPM, DEC);
  LCD.display();
}


