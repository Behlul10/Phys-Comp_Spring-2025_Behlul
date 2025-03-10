/**********************************************************************************************************************
************************************4 LEDS , 4 sequences******************************************
**********************************************************************************************************************/

// Define LED pins
const int led1 = 2;
const int led2 = 4;
const int led3 = 5;
const int led4 = 18;


int patternNumber = 0; //current pattern (0-3 patterns)
unsigned long patternDuration = 5000; // Each pattern runs for 5 seconds
unsigned long startTime = 0;  // When current pattern started


void setup() 
{
  // Set all LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  // Initialize timer
  startTime = millis();
}

void loop() {

  // Check if it's time to change patterns
  if (millis() - startTime > patternDuration) {
    // Move to next pattern
    patternNumber = (patternNumber + 1) % 4;
    startTime = millis();
    
    // Pause between patterns
    delay(1000);
  }
  
  // Execute the current pattern
  if (patternNumber == 0) {
    // Pattern 1: First LED pattern
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  } 
  else if (patternNumber == 1) {
    // Pattern 2: Second LED pattern
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } 
  else if (patternNumber == 2) {
    // Pattern 3: Third LED pattern
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } 
  else if (patternNumber == 3) {
    // Pattern 4: Fourth LED pattern
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }
  
  delay(100);}
