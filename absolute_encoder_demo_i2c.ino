
#include <SPI.h>
#include <Wire.h>
#include "Adafruit_MCP23017.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MONITOR_LED LED_BUILTIN

Adafruit_MCP23017 mcp0;

char pout[52] = {0};
#include "settings.h"
ENCODER enc;
OLEDTEXT oledText;
#include "oled_functions.h"
#include "encoder_functions.h"

void setup() {

  delay(1000);
  Serial.begin(9600);
  Serial.println("ready");

  pinMode(MONITOR_LED, OUTPUT);
  
  digitalWrite(MONITOR_LED, HIGH);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

   // Clear the buffer
  display.clearDisplay();

  mcp0.begin(0);      // 0 = i2c address 0x20

  // setup GPA for input
  for (byte n = 0; n <= 7; n++) {
    mcp0.pinMode(n, INPUT);
    mcp0.pullUp(n, HIGH);  // turn on the internal 100K pullup
  }

  // setup GPB for output
  for (byte n = 8; n <= 15; n++) {
    mcp0.pinMode(n, OUTPUT);
    mcp0.digitalWrite(n, LOW); // turn LED on
  }

  delay(500);
  for (byte n = 15; n >= 8; n--) {
    sprintf(oledText.line1,"LED: %i", n-8);
    oledTextOutput();
    mcp0.digitalWrite(n, HIGH); // turn LED off   
    delay(300);
  }

  display.clearDisplay();

  // uncomment the following to setup the enc.values array
  // once complete, copy and paste to replace the ENCODER.values array in settings.h
  //setupEncoderValues();

  enc.value = getCurrentEncoderVal();  // get start position
  enc.lastValue = enc.value;
  sprintf(oledText.line1,"index    : %i", enc.lastIndex);
  sprintf(oledText.line2,"value    : %3i, 0x%02X", enc.value, enc.value);
  sprintf(oledText.line3,"bin value: %s", enc.binVal);
  sprintf(oledText.line4,"direction: %s", (enc.rotation ? " CW" : "CCW" ));
  oledTextOutput();
  displayEncoderVal();

  digitalWrite(MONITOR_LED, LOW);

}

void loop() {

  enc.value = readEncoder();

  if (enc.value > 0 && (enc.value != enc.lastValue))
  {
    digitalWrite(MONITOR_LED, HIGH);
    encoderDirection(enc.value); // sets enc.rotation and enc.lastIndex

    sprintf(oledText.line1,"index    : %i", enc.lastIndex);
    sprintf(oledText.line2,"value    : %3i, 0x%02X", enc.value, enc.value);
    sprintf(oledText.line3,"bin value: %s", enc.binVal);
    sprintf(oledText.line4,"direction: %s", (enc.rotation ? " CW" : "CCW" ));
    oledTextOutput();

    sprintf(pout,"%s, 0x%02X, %3i", enc.binVal, enc.value, enc.value);
    Serial.println(pout);

    //showEncoderVal(enc.value); // alternative to enc.binVal - converts the byte into a binary string for display

    displayEncoderVal(); // illuminate the LED's
    
    delay(200);
    enc.lastValue = enc.value;
    digitalWrite(MONITOR_LED, LOW);
  }

  delay(10);
}
