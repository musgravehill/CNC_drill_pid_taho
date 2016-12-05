void LCD_init() {
  LCD.begin();
  LCD.setContrast(50);
  LCD.clearDisplay();


  // text display tests
  LCD.setTextSize(1);
  LCD.setTextColor(BLACK);
  LCD.setCursor(0, 0);
  LCD.println("Hello, world!");
  LCD.setTextSize(2);
  LCD.println(0xDEADBEEF, HEX);
  LCD.display();
}
