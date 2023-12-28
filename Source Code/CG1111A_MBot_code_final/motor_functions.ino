/**************** Basic Directional Control ****************/
/*
moveForward: forward movement, adjusted with PID
stopMotor: stops motor for specified duration
*/
void moveForward() {
  float deviation = computePID();
  Serial.println(deviation);
  if (deviation == -1) {
    leftMotor.run(-FORWARD_SPEED);
    rightMotor.run(FORWARD_SPEED);
  }
  else {
    leftMotor.run(-FORWARD_SPEED - deviation);
    rightMotor.run(FORWARD_SPEED - deviation);
  }
}


void stopMotor(int duration) {
  leftMotor.stop();
  rightMotor.stop();
  delay(duration);
}


void oneGridForward() {
  leftMotor.run(-FORWARD_SPEED);
  rightMotor.run(FORWARD_SPEED);
  delay(ONE_GRID_TIME);
  stopMotor(TURN_DELAY);
}


void leftTurn() {
  leftMotor.run(TURN_SPEED);
  rightMotor.run(TURN_SPEED);
  delay(TURN_TIME);
  stopMotor(TURN_DELAY);  
}


void rightTurn() {
  leftMotor.run(-TURN_SPEED);
  rightMotor.run(-TURN_SPEED);
  delay(TURN_TIME);
  stopMotor(TURN_DELAY);
}

void uTurn() {
  leftMotor.run(TURN_SPEED);
  rightMotor.run(TURN_SPEED);
  delay(UTURN_TIME);
  stopMotor(TURN_DELAY);
}


void doubleLeftTurn() {
  leftTurn();
  oneGridForward();
  leftTurn();
}


void doubleRightTurn() {
  rightTurn();
  oneGridForward();
  rightTurn();
}


void stopMotorIndefinitely() {
  leftMotor.stop();
  rightMotor.stop();
  
  // Enter an infinite loop to prevent the program from proceeding
  while (true) {
    delay(10);
  }
}
