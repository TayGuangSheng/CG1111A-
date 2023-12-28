#include <MeMCore.h>

// Settings
#define LDR A2
#define RGB_WAIT 100
#define LDR_WAIT 10
#define LED_PIN 13   
MeRGBLed led(0, 30);  // Initialise the RGB LED object

// Colour Calibration Settings
#define CAL_NO 10
float whiteArray[] = {591.00, 810.00, 802.00};  // Array to store calibrated white values
float blackArray[] = {108.00, 241.00, 294.00};  // Array to store calibrated black values
float greyDiff[] = {-483.00, -569.00, -508.00}; // Array to store differences between black and white values

// Colour Value Arrays
#define DET_NO 20                     // Number of readings to take during colour detection
#define MIN_DEV 9999                  // Minimum deviation threshold for colour matching
#define redArray {290, 150, 110}      // Red colour calibration values
#define greenArray {36,151, 111}      // Green colour calibration values
#define orangeArray {312, 180, 118}   // Orange color calibration values
#define purpleArray {128, 157, 188}   // Purple color calibration values
#define blueArray {39, 187, 227}      // Blue color calibration values
static int coloursArray[5][3] {redArray, greenArray, orangeArray, purpleArray, blueArray};  // Array of calibrated colour values
static int displayArray[5][3] {
  {255, 0, 0},   // Red
  {0, 255, 0},   // Green
  {255, 50, 0},  // Orange
  {128, 0, 128}, // Purple
  {0, 0, 255}    // Blue
};
float colourArray[] = {0, 0, 0};


/* LED Control Functions
shineRed, shineBlue, shineGreen, shineNone: Shines respective colours
shineRGB: Shines R, G, B in succession
*/
void shineRed() {             // Code for turning on the red LED only
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  }
void shineGreen() {           // Code for turning on the green LED only
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
}
void shineBlue() {             // Code for turning on the blue LED only
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
}
void shineNone() {             // Code for turning off all LEDs
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
}
void shineRGB(int colour) {    //Code to simulate RGB LED
  switch(colour) {
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


// Function to obtain an average reading from the LDR
int getAvgReading(int times) {
  int reading;
  int total = 0;

  for(int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total += reading;
    delay(LDR_WAIT);    // Wait between readings
  }
  return total/times;   // Return the average reading
}


// Function to set the calibration balance for white and black colours
void setBalance() {
  for (int i = 0; i <= 1; i++) {
    (i == 0) ? Serial.println("WHITE PAPER") : Serial.println("BLACK PAPER");
    delay(5000);
    for(int j = 0; j <= 2; j++)
      {
        shineRGB(j);  // Shine the corresponding colour
        delay(RGB_WAIT);  // Wait for the colour to settle
        if (i == 0) {
          whiteArray[j] = getAvgReading(CAL_NO);        // Store the average reading for white 
        } else {
          blackArray[j] = getAvgReading(CAL_NO);        // Store the average reading for black
          greyDiff[j] = blackArray[j] - whiteArray[j];  // Calculate the difference  
        }
        shineNone();    // Turn off LED
        delay(RGB_WAIT);
      }
  }
  Serial.println("CALIBRATION COMPLETE");
}


/*
Colour Detection Function
Returns int 0: Red, 1: Green, 2: Orange, Purple: 3, Light Blue: 4
*/
int detectColour() {
  // Shine RGB, read LDR after some delay
  int det = -1;
  int min_dev = MIN_DEV;
  long curr_dev;
  //Serial.println("DETECTING COLOUR");
  for(int c = 0; c <= 2; c++) {
    shineRGB(c);
    delay(RGB_WAIT);
    colourArray[c] = getAvgReading(DET_NO);
    colourArray[c] = abs((colourArray[c] - blackArray[c])/(greyDiff[c])*255);
    shineNone();
    //delay(RGB_WAIT);
    }


  // Run algorithm for colour decoding (Sum of Squares)
    for (int i = 0; i < 5; i++) {
      curr_dev = 0;
      // Takes the sum of square values of difference between current colour detected
      // and reference values saved in allColourArray
      for (int j = 0; j < 3; j++) {
        curr_dev += (coloursArray[i][j]-colourArray[j])*(coloursArray[i][j]-colourArray[j]);
      }
      if (curr_dev < min_dev && curr_dev > 0) {
        det = i;
        min_dev = curr_dev;
      }
  }
  if (det > -1) { 
    led.setColorAt(0, displayArray[det][0], displayArray[det][1], displayArray[det][2]); // set Right LED to Detected Colour
    led.setColorAt(1, displayArray[det][0], displayArray[det][1], displayArray[det][2]);
    led.show();
  } else {
    for(int i = 0; i < 5; i++) {
      led.setColorAt(0, displayArray[i][0], displayArray[i][1], displayArray[i][2]); // set Right LED to Detected Colour
      led.setColorAt(1, displayArray[i][0], displayArray[i][1], displayArray[i][2]);
      led.show();
      delay(500);
    }
  }
  return det;
  }


void setup()
{
  // Configure pinMode for A0, A1, A2, A3
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(LDR, INPUT);

  Serial.begin(9600);
  led.setpin(LED_PIN);
  led.setColorAt(0, 0, 0, 0); // set Right LED to OFF
  led.setColorAt(1, 0, 0, 0); // set Left LED to OFF
  led.show();
  
  // The following lines are to be commented out during the calibration of the other colours
  // setBalance(); // Runs calibration function
  // delay(2000);
  // Serial.println("WHITE");
  // Serial.println(whiteArray[0]);
  // Serial.println(whiteArray[1]);
  // Serial.println(whiteArray[2]);
  // Serial.println("BLACK");
  // Serial.println(blackArray[0]);
  // Serial.println(blackArray[1]);
  // Serial.println(blackArray[2]);
  // Serial.println("GREY");
  // Serial.println(greyDiff[0]);
  // Serial.println(greyDiff[1]);
  // Serial.println(greyDiff[2]);
  // End of white and black calibration

}


void loop() {
  // The following lines are to be commented out during the calibration of black and white colour
  int i;
  Serial.println("detecting");
  i = detectColour();
  Serial.println(i);
  Serial.println(colourArray[0]);
  Serial.println(colourArray[1]);
  Serial.println(colourArray[2]);
  delay(2000);
  // End of colour calibration 
}

