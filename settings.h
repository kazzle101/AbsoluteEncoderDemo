
struct ENCODER {

  byte value = 0;

  // see setupEncoderValues() in encoder_functions.h to see how this is set.
  byte values[128] = {142, 14, 46, 38, 6, 2, 18, 82, 83, 211, 195, 203, 235, 239, 231, 199, 71, 7, 23, 19, 3, 1, 9, 41, 169, 233, 225, 229, 
                      245, 247, 243, 227, 163, 131, 139, 137, 129, 128, 132, 148, 212, 244, 240, 242, 250, 251, 249, 241, 209, 193, 197, 196, 
                      192, 64, 66, 74, 106, 122, 120, 121, 125, 253, 252, 248, 232, 224, 226, 98, 96, 32, 33, 37, 53, 61, 60, 188, 190, 254, 
                      126, 124, 116, 112, 113, 49, 48, 16, 144, 146, 154, 158, 30, 94, 95, 127, 63, 62, 58, 56, 184, 152, 24, 8, 72, 73, 77, 
                      79, 15, 47, 175, 191, 159, 31, 29, 28, 92, 76, 12, 4, 36, 164, 166, 167, 135, 151, 215, 223, 207, 143};
  const byte count = 128;                      
  boolean rotation = false; // true = clockwise, false = anticlockwise
  byte lastValue = 0;
  byte lastIndex = 0;
  char binVal[9] = {0};
};

struct OLEDTEXT {
  char line1[21] = {0};
  char line2[21] = {0};
  char line3[21] = {0};
  char line4[21] = {0};
};
