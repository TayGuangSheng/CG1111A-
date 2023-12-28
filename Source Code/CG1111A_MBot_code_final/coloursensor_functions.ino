/**************** Detect Black Line ****************/
// This function checks if the mBot has reached a waypoint(black line)
bool reachWayPoint() {
  int sensorState = lineFinder.readSensors();
  if (sensorState == S1_IN_S2_IN) { // The condition checks if both sensors (S1 and S2) are detecting the black line
    return true;
  } else {
    return false;
  }
}

/**************** RGB Control Functions ****************/
/*
shineRed, shineBlue, shineGreen, shineNone: Shines respective colours
shineRGB: Shines R, G, B based on input to simulate RGB LED
*/
void shineRed() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
}
void shineGreen() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
}
void shineBlue() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
}
void shineNone() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
}
void shineRGB(int colour) {
  switch (colour) {
    case 0:
      shineRed();
      break;
    case 1:
      shineGreen();
      break;
    case 2:
      shineBlue();
      break;
  }
}


/**************** Colour Detection Functions ****************/
/*
getAvgReading: returns int average of multiple LDR readings
setBalance: detects black and white paper, prints calibrated white, black and greyDiff arrays
detectColour: returns int 0: Red, 1: Green, 2: Orange, Purple: 3, Light Blue: 4 
*/

int getAvgReading(int times) {
  int reading;
  int total = 0;

  for (int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total += reading;
    delay(LDR_WAIT);
  }
  return total / times;
}


int detectColour() {
  // 1. Shine RGB, read LDR after some delay
  int det = -1;
  int min_dev = MIN_DEV;
  long curr_dev;
  for (int i = 0; i <= 2; i++) {
    shineRGB(i);
    delay(RGB_WAIT);
    colourArray[i] = getAvgReading(DET_NO);
    colourArray[i] = abs((colourArray[i] - blackArray[i]) / (greyDiff[i]) * 255);
    shineNone();
  }

  // 2. Run algorithm for colour decoding (Sum of Squares)
  for (int i = 0; i < 5; i++) {
    curr_dev = 0;

    for (int j = 0; j < 3; j++) {
      curr_dev += (coloursArray[i][j] - colourArray[j]) * (coloursArray[i][j] - colourArray[j]);
    }
    if (curr_dev < min_dev && curr_dev > 0) {
      det = i;
      min_dev = curr_dev;
    }
  }

  // 3. Set MBot onboard LED to display array colours
  if (det > -1) {
    led.setColor(displayArray[det][0], displayArray[det][1], displayArray[det][2]); 
    led.show();
  }
  return det;
}
