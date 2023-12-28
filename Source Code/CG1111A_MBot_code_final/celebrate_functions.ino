/**************** CELEBRATE FUNCTION ****************/

// Function to play a series of musical notes and changes LED colours accordingly
void celebrate() {
  int noteDuration;
  int pauseBetweenNotes;
  int colour;

  // Loop through the CrazyFrog melody arrays
  for (int i = 0; i < 31; i++) {
    noteDuration = 1000 / CrazyFrog_duration[i];
    buzzer.tone(CrazyFrog_note[i], noteDuration);  // Play the note on the buzzer for the calibrated duration 
    pauseBetweenNotes = noteDuration * TEMPO;      // Calculate the pause between notes based on the Tempo 
    colour = i % 5;                                // Cycles through 5 colours
    led.setColorAt(0, displayArray[colour][0], displayArray[colour][1], displayArray[colour][2]);  // Set Right LED to Detect Colour
    led.setColorAt(1, displayArray[colour][0], displayArray[colour][1], displayArray[colour][2]);  // Set Left LED to the same Colour
    led.show();
    delay(pauseBetweenNotes);  // Pause between notes to create a rhythm 
    }
buzzer.noTone();  // Stop playing any tone
}

