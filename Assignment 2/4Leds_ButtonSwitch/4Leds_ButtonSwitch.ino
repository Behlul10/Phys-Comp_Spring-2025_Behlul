/**********************************************************************************************************************
************************************4 LEDS , 4 sequences with button switches******************************************
**********************************************************************************************************************/


const int buttonPin = 0;
const int ledPins[] = {2, 4, 5, 18}; 
const int numLeds = 4;

int buttonState = 0; //on off switch
int lastButtonState = HIGH;
int pattern = 0; //counting the patterns

void setup() 
{
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
    for(int i = 0; i < numLeds; i++) // add led until amount of total leds 
    {
      pinMode(ledPins[i], OUTPUT); 
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);// check if button is on or off

  if (buttonState == LOW && lastButtonState == HIGH) 
  {
    pattern = (pattern + 1) % 4; //Cycle through patterns. checking remainder of the #'s  pattern, resets back to 0 (1st pattern) on 4th pattern
    delay(200);
  }
  //instead of an if-else statment we use a switch case
  switch(pattern){
    case(0):
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[1], LOW);
        digitalWrite(ledPins[2], HIGH);
        digitalWrite(ledPins[3], HIGH);
        break;

    case(1):
        digitalWrite(ledPins[0], LOW);
        digitalWrite(ledPins[1], LOW);
        digitalWrite(ledPins[2], LOW);
        digitalWrite(ledPins[3], HIGH);
        break;

    case(2):
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[1], HIGH);
        digitalWrite(ledPins[2], LOW);
        digitalWrite(ledPins[3], HIGH);
        break;
    case(3):
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[1], LOW);
        digitalWrite(ledPins[2], LOW);
        digitalWrite(ledPins[3], HIGH);
        break;
  }

  lastButtonState = buttonState; // update button state

}
