/*********************************************************************************************************************
*****************************************************    Midterm WIP   **********************************************
*********************************************************************************************************************/



//initilize
const int buttonPin = 0;
const int LEDPin = 4;
const int potPin = 1;
const buzzerPin = 2;

int ledState = LOW;               // current LED state

void setup() 
{
  pinMode(buttonPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
    
  analogReadResolution(11); //analog res to 11 bits (0 - 2047)

  //pizeo output
}

void loop() 
{
  int buttonState = digitalRead(buttonPin);
  int potValue = analogRead(potPin);
  
  // Map pot value (0 to 2047) to a tone frequency range (e.g., 200 to 2000 Hz) for buzzer
  int toneFreq = map(potValue, 0, 2047, 200, 2000);


  if (buttonPin == HIGH)
  {
    digitalWrite(LEDPin, high); //indicate that device is on
    
    // Activate the buzzer with a tone based on the potentiometer reading
    tone(buzzerPin, toneFreq);
  } 
  else if (buttonPin == LOW)
  {
    digitalWrite(LEDPin, LOW); // indicate that device off
    // Turn off the buzzer
    noTone(buzzerPin);
  } 
}
