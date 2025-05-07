const int adcPin_1 = 1;
const int adcPin_2 = 2;
const int buttonPin_1 = 20;
const int buttonPin_2 = 21;

bool buttonState_1 = 0;
bool buttonState_2 = 0;

int adcRead_1 = 0;
int adcRead_2 = 0;

int lastTime = 0;
int currentTime = 0;
int timerInterval = 20;

void setup() 
{
  pinMode(buttonPin_1, INPUT_PULLUP); 
  pinMode(buttonPin_2, INPUT_PULLUP);
  analogReadResolution(8);  
  Serial.begin(115200);
}

void loop() 
{
  adcRead_1 = map(analogRead(adcPin_1), 0, 255, -128, 127);
  adcRead_2 = map(analogRead(adcPin_2), 0, 255, -128, 127);

  buttonState_1 = !digitalRead(buttonPin_1);
  buttonState_2 = !digitalRead(buttonPin_2);

  currentTime = millis(); 
  if (currentTime - lastTime >= timerInterval)
  {
    lastTime = currentTime; 
    Serial.write(buttonState_1); 
    Serial.write(buttonState_2);  
    Serial.write(adcRead_1);      
    Serial.write(adcRead_2);      
    Serial.write('e');            
  }
}