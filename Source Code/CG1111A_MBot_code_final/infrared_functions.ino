/**************** INFRARED SENSOR ****************/
// Functions to turn on/off IR emitter
void turnOnIR() {
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
}


void turnOffIR() {
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
}


float infraredSensorDistance() {
  // Activate the IR emitter
  turnOnIR();
  delayMicroseconds(IR_WAIT); // Allow time for the IR emitter to stabilize

  // Measure the distance using the IR receiver
  int initialReading = analogRead(IR_PIN);

  turnOffIR();
  delayMicroseconds(IR_WAIT);
  int finalReading = analogRead(IR_PIN);

  // Calculate the difference in sensor readings
  float voltageDifference = initialReading - finalReading;
  
  // Calculate and return the distance
  return calculateDistance(voltageDifference);
}



float calculateDistance(float voltageDifference) {
  if (voltageDifference == OFFSET) { // Avoid division by zero
    return -1; // Indicate an error or invalid distance
  }

  float distance = sqrt(IR_CALIBRATION_FACTOR / (voltageDifference - OFFSET));
  return distance;
}


// Function to reduce noise in the infrared sensor readings
float previousFilteredDistance = 0.0;
float filteredDistance() {
  float distance = infraredSensorDistance();
  
  // Determines whether the change in distance is significant enough to be considered noise or real movement 
  if (abs(distance - previousFilteredDistance) > THRESHOLD) {
    return distance;
  } else {
    // Apply a smoothing algorithm: calculate a weighted average of the previous filtered distance and the current distance
    return (1 - SMOOTHING_FACTOR) * previousFilteredDistance + (SMOOTHING_FACTOR * distance);
  }
}