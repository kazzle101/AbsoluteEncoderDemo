// used to establish the direction of rotation
// enc.direction - clockwise = true, counter-clockwise = false
void encoderDirection(byte val) {

  // finds the current index by value in enc.values
  byte index = 0;

  while (index < enc.count) {
    if (enc.values[index] == val) {
      break;
    }
    index++;
  }

  // exit if no change
  if (index == enc.lastIndex) {
    return enc.rotation;
  }

  // the first two are a boundary checks, turning over the 360 degree limit to start again;
 
  // gotten to the start of the enc.values array while turning counter-clockwise
  if (enc.lastIndex == 0 && index == (enc.count - 1)) {
    enc.rotation = false;
  }
  // gotten to the end of the enc.values array while turning clockwise
  else if (enc.lastIndex == (enc.count - 1) && index == 0) {
    enc.rotation = true;
  }
  // turning counter-clockwise
  else if (index < enc.lastIndex) {
    enc.rotation = false;
  }
  // turning clockwise
  else {
    enc.rotation = true;
  }

  enc.lastIndex = index;

}

// read the encoder pins
// the char array enc.binVal is built in reverse so as to show the state of the encoder on GPA 
// directly across the MCP23017. So, for example, when GPA7 is high, the LED on GPB0 will be lit.
byte getCurrentEncoderVal() {

  enc.binVal[0] = {0};
  bool p;
  byte readEnc = 0;
  byte i = 7;

  for (byte n = 0; n < 8; n++) {
    p = mcp0.digitalRead(n);
    readEnc |= (byte)p << n;
    enc.binVal[i] = (p == true ? '1' : '0');    
    i--;
  }

  return readEnc;
}


void displayEncoderVal() {

  bool p;
  for (byte n = 0; n < 8; n++) {
    p = (enc.binVal[n] == '1' ? true : false);
    mcp0.digitalWrite(n+8, !(p));
  }
  
}

// converts the byte vlaue into a char array in binary format for showing on the display
void showEncoderVal(byte val) {

  char dout[9] = {0};
  byte i = 0;
  byte c = 7;
  
  while (i <= 7) {
    if ((val >> i) & 1) {
      dout[c] = '1';
    }
    else {
      dout[c] = '0';
    }
    i++;
    c--;
  }

  Serial.println(dout);  
}

// read the current encoder value
byte readEncoder() {
  
  byte value = getCurrentEncoderVal();

  if (value == 255) {
    return 0;
  }
  
  return value;
}

// used to prevent duplicate entries when setting up
boolean inEncoderArray(byte values[], byte val) {
  for (byte i = 0; i < enc.count; i++) {
    if (values[i] == val) {
      return true;
    }
  }
  return false;
}


// used when setting up the encoder, rotate the encoder to get all 128 values on the
// output - it will then show an array to copy and paste to replace the ENCODER.values array in settings.h
// carefully rotate the encoder so it doesn't skip positions.
void setupEncoderValues() {

  char iout[40] = {0};
  int c = 0;
  byte values[128] = {0};
  char valString[600] = {0};

  for (byte i = 0; i < enc.count; i++) {
    enc.values[i] = 0;
  }

  Serial.println("Setup: Steadily rotate encoder clockwise until .:STOP:. appears");

  while (true) {
 
    digitalWrite(MONITOR_LED, HIGH);

    byte val = readEncoder();
    if (val == 0) {
      continue;
    }

    if (c >= enc.count) {
      Serial.println(".:STOP:.");
      break;
    }

    if (inEncoderArray(values, val)) {
      continue;
    }
    
    values[c] = val;

    sprintf(iout, " %3i, %3i", c, val);
    Serial.println(iout);

    c++;
    digitalWrite(MONITOR_LED, LOW);
  }

  char sVal[4];
  for (byte i = 0; i < enc.count; i++) {
    itoa(values[i],sVal,10);    
    strcat(valString, sVal);
    strcat(valString,", ");    
    enc.values[i] = values[i];
  }
  int lastChar = strlen(valString);
  valString[lastChar-2] = '\0';  // removes the last ', ' from the end

  Serial.print("byte values[128] = {");
  Serial.print(valString);
  Serial.println("};");
  Serial.println(" ");

  digitalWrite(MONITOR_LED, LOW);
}
