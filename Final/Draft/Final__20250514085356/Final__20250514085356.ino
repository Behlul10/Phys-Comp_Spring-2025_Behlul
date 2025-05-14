/*
///////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// Final Project///////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
*/
const int buttonPin_1 = 20;
bool buttonState_1 = 0;

#define VRX_PIN  4
#define VRY_PIN  5
int xValue = 0; //store X axis
int yValue = 0; //store Y axis

void setup() 
{
  pinMode(buttonPin_1, INPUT_PULLUP); 
  // analogReadResolution(11);  
  Serial.begin(9600);
}

void loop() 
{
  buttonState_1 = !digitalRead(buttonPin_1);
  Serial.println(buttonState_1);
  Serial.write(buttonState_1); 

  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);

  Serial.write(xValue);
  Serial.write(yValue);

  // print data to Serial Monitor on Arduino IDE
  Serial.println("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  delay(100);

}

