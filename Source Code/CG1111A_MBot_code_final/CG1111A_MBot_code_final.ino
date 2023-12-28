#include <MeMCore.h>


/**************** DEFINES & CONSTANTS ****************/
// Pins Constants
#define PUSH_BUTTON A7
#define IR_PIN A3
#define LDR A2
#define LED_PIN 13


// Celebrate Constants (COPIED)
#define TEMPO 1.05
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637  
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186


// Movement Constants
#define FORWARD_SPEED 255
#define TURN_SPEED 255
#define TURN_TIME 305        // Duration for left and right turn
#define UTURN_TIME 552       // Duration for U-turn
#define ONE_GRID_TIME 730    // Duration to travel one grid 
#define TURN_DELAY 500 


// Ultrasonic Constants
#define TIMEOUT 2000
#define SPEED_OF_SOUND 340
#define ULTRASONIC 10


// Infrared Constants
#define IR_CALIBRATION_FACTOR -0.1291 // Calibration factor for distance calculation
#define OFFSET 901.21             // Offset value for distance calculation
#define IR_WAIT 10                    // Wait time for IR emitter stabilization in microseconds

// Smoothing Algorithm Constants
#define SMOOTHING_FACTOR 0.1 
const int THRESHOLD = 2;                            // Change in value within the threshold would be considered as noise and will be ignored


// Proportional Integral Derivative Constants
#define PROPORTIONAL_GAIN 33.0                      // Proportional constant to correct a setpoint proportional to the difference
#define DERIVATIVE_GAIN 800.0                       // Derivative constant to prevent overshooting by slowing the correction applied as robot gets closer to the setpoint
#define SET_POINT 10.0                              // With the mBot remaining at the centre of the maze path, the ultrasonic sensor is 10cm away from the right wall
#define MAX_CONTROL_OUTPUT 50.0                     // To prvent overcompensation of error 


// Colour Calibration Settings
#define CAL_NO 10                                   // Number of values taken for calibration
#define RGB_WAIT 100                                // Duration for RBG LED lighting up 
#define LDR_WAIT 10                                 // Duration for LDR to read values
float whiteArray[] = {591.00, 810.00, 802.00};
float blackArray[] = {108.00, 241.00, 294.00};
float greyDiff[] = {-483.00, -569.00, -508.00};     // Difference of the black and white array


// Colour Value Arrays
#define DET_NO 20                   
#define MIN_DEV 9999
#define redArray {290, 150, 110}                   // Red values after calibration
#define greenArray {36,151, 111}                   // Green values after calibration
#define orangeArray {268, 175, 112}                // Orange values after calibration
#define purpleArray {128, 157, 188}                // Purple values after calibration
#define blueArray {39, 187, 227}                   // Blue values after calibration
static int coloursArray[5][3] {redArray, greenArray, orangeArray, purpleArray, blueArray};
static int displayArray[5][3] {                    // For displaying the LED on the mBot 
  {255, 0, 0},     // Red
  {0, 255, 0},     // Green
  {255, 50, 0},    // Orange
  {128, 0, 128},   // Purple
  {0, 0, 255}      // Blue 
};
float colourArray[] = {0, 0, 0};


/**************** INITIALISE MBOTS PORT ****************/
MeBuzzer buzzer;
MeDCMotor leftMotor(M1);                 // Assigning left motor to port M1
MeDCMotor rightMotor(M2);                // Assigning right motor to port M2
MeUltrasonicSensor ultraSensor(PORT_2);  // Assigning ultrasonic sensor to port 2
MeLineFollower lineFinder(PORT_1);       // Assining linefinder to port 1
MeRGBLed led(0, 30);                     // Creates LED object based on static hardware connections on mCore 


/**************** CELEBRATE ****************/
// Notes to be played
int CrazyFrog_note[] = {
 NOTE_D4, 0, NOTE_F4, NOTE_D4, 0, NOTE_D4, NOTE_G4, NOTE_D4, NOTE_C4,
 NOTE_D4, 0,  NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_AS4, NOTE_A4, NOTE_F4,
 NOTE_D4, NOTE_A4, NOTE_D5, NOTE_D4, NOTE_C4, 0, NOTE_C4, NOTE_A3, NOTE_E4, NOTE_D4,
 0,NOTE_D4,NOTE_D4
};


// Tempo of notes to be played 
int CrazyFrog_duration[] = {
 8, 8, 6, 16, 16, 16, 8, 8, 8,
 8, 8, 6, 16, 16, 16, 8, 8, 8,
 8, 8, 8, 16, 16, 16, 16, 8, 8, 2,
 8,4,4
};


/**************** Proportional Integral Derivative (PID) ****************/
float previousError   = 0.0;   


/**************** CHALLENGE ****************/
void challenge() {
  int LDR = detectColour();  // Each LDR number corresponds to a specific colour detected.
  if (LDR == 0) {            // Red
    leftTurn();
  } else if (LDR == 1) {     // Green
    rightTurn();
  } else if (LDR == 2) {     // Orange 
    uTurn();
  } else if (LDR == 3) {     // Purple 
    doubleLeftTurn();
  } else if (LDR == 4) {     // Blue
    doubleRightTurn();
  } else {
    celebrate();
    stopMotorIndefinitely();
  }
}


/**************** MAIN FUNCTION ****************/
void setup() {
  pinMode(PUSH_BUTTON, INPUT);
  pinMode(IR_PIN, INPUT);
  // Configure pinMode for A0, A1, A2, A3
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(LDR, INPUT);
  led.setpin(13);
}


void loop() {
  moveForward();              // Commands the mBot to move forward continuously
  if(reachWayPoint()){        // Checks if the mBot has detected any blackline(waypoint)
    stopMotor(10);
    challenge();              // To sense the colour and carry out the actions corresponding to the colour 
  }
}