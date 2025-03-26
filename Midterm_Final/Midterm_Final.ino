//midterm

// Potentiometer setup
const int potPin = 1;
const int numReads = 20; // Number of readings for averaging
int reading[numReads];
int count = 0;

// Piezo buzzer setup
const int piezoPin = 21;
const int piezoTPin = 47;
// Button setup
const int buttonPin = 0;

bool buttonState = LOW; //on off switch
bool lastButtonState = HIGH; // Tracks the previous state of the button
bool buzzerState = false; // Tracks whether the buzzer is on or off

void setup() 
{
  Serial.begin(115200);

  // Set resolution for analog read
  analogReadResolution(11);

  // Set button pin as input
  pinMode(buttonPin, INPUT_PULLDOWN);
}

void loop() 
{
  // Read the button state
  bool currentButtonState = digitalRead(buttonPin);
  
  // buttonState = digitalRead(buttonPin);

  // if (buttonState == LOW && lastButtonState == HIGH)
  // {
  //   Serial.println("Button is.. pressed");
  //   lastButtonState = buttonState; // update button state
  // }

  if(currentButtonState == LOW){
    Serial.println("Button being pressed down");
    // tone(piezoTPin,100);
    tone(piezoTPin, 2000); // Play tone at the mapped frequency

  }
  else if (currentButtonState == HIGH){
    Serial.println("BUTTON not being pressed down");
    noTone(piezoTPin);

    //!buzzerState;
  }
  // Check if the button was pressed (transition from HIGH to LOW)
  if (currentButtonState == LOW ) //&& lastButtonState == HIGH
  {
    // Toggle the buzzer state
    buzzerState = !buzzerState;

    // Print the state of the buzzer
    if (buzzerState) //== HIGH
    {
      Serial.println("Buzzer is ON");
    } 
    else 
    {
      Serial.println("Buzzer is OFF");
      noTone(piezoPin);
    }

    // Debounce delay
    delay(50);
  }

  //Update the last button state
  lastButtonState = currentButtonState;

  // If the buzzer is on, control the frequency with the potentiometer
  if (buzzerState) 
  {
    // Read and average potentiometer values
    reading[count] = analogRead(potPin);
    count++;

    if (count >= numReads)
    {
      count = 0;
    }

    int sum = 0; 
    for (int i = 0; i < numReads; i++)
    {
      sum += reading[i];
    }

    int analogValue = sum / numReads;

    // Map the averaged potentiometer value to a frequency range
    int frequency = map(analogValue, 0, 1466, 100, 1000); // Map to frequency range (100 Hz to 1000 Hz)

    // Generate a continuous tone on the piezo buzzer
    tone(piezoPin, frequency); // Play tone at the mapped frequency

    // Print debug information
   // Serial.printf("ADC raw = %i \t ADC averaged = %i \t Frequency = %i Hz\n", analogRead(potPin), analogValue, frequency);
  } 
  else 
  {
    // Turn off the buzzer if it's off
    noTone(piezoPin);
  }

  delay(50); // Small delay for stability
}
