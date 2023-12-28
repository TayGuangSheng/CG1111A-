/**************** PID FUNCTION ****************/

// Function to compute the output of the PID (Proportional-Integral-Derivative) controller.
float computePID() {
    float currentDistance = ultrasonicSensorDistance();
    
    // If the ultrasonic sensor does not detect the wall, IR sensor will be activated
    if (currentDistance > SET_POINT * 1.5) {
       currentDistance == 27 - (filteredDistance() + 9);
    }

    // Check if no walls detected on both sides 
    if (currentDistance == 0.0 || currentDistance > SET_POINT * 1.5) {
        previousError = 0.0;
        return -1;
    }
    
    float error = currentDistance - SET_POINT;
  
    // Calculate the adjusted output using the proportional and derivative gains.
    float adjustedOutput = PROPORTIONAL_GAIN * error + DERIVATIVE_GAIN * (error - previousError);
    previousError = error;
    
    // This prevents the motor from receiving a signal that's too high.
    if (adjustedOutput > MAX_CONTROL_OUTPUT) {
        adjustedOutput = MAX_CONTROL_OUTPUT;
    } else if (adjustedOutput < -MAX_CONTROL_OUTPUT) {
        adjustedOutput = -MAX_CONTROL_OUTPUT;
    }

    return adjustedOutput;
}


/**************** ULTRASONIC SENSOR ****************/

// Function to measure distance using the ultrasonic sensor 
float ultrasonicSensorDistance() {
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);
  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  float distanceCm = 0.5 * duration * SPEED_OF_SOUND * (0.0001);
  return distanceCm;
}