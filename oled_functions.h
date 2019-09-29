
void clearOLEDtext() {

  oledText.line1[0] = {0};
  oledText.line2[0] = {0};
  oledText.line3[0] = {0};
  oledText.line4[0] = {0};
}

void oledTextOutput() {

  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  
  display.println(F(oledText.line1));
  display.println(F(oledText.line2));
  display.println(F(oledText.line3));
  display.println(F(oledText.line4));

  display.display();

  clearOLEDtext();
}
