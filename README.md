# Absolute Encoder Demo

Demonstrating the use of an Absolute Contacting Encoder over I2C with an Arduino

This Arduino sketch shows a method of decoding a Bournes EAW - Absolute Contacting Encoder (ACE) - EAW0J-B24-AE0128L, a rotary encoder switch that provides an 8-bit code with 128 absolute states to your microcontroller of choice.

In this case I have used an MCP23017 I2C 16 bit IO expander to send the code to an Ardunio compatible Teensy which then sends the received binary code back to the IO expander to light a row of LED's and also show information on an attached I2C SSD1306 OLED display. The code also determines which way the encoder has been turned.

Circuit diagram:
<img src="https://github.com/kazzle101/absolute_encoder_demo/blob/master/absolute_encoder_demo_s.png">
