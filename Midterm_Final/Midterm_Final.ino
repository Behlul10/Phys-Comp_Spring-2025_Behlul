const int potPin = 1;

const int numReads = 20; //number of readings in avg, increase to smooth out more
int reading[numReads];
int count = 0;

void setup() 
{
  Serial.begin(115200);

  analogReadResolution(11);
}

void loop() 
{
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

  Serial.println(analogValue);
  int mapVal = map(analogValue, 0, 1466, 0, 255);

  rgbLedWrite(38, mapVal, 0, 0);

  Serial.printf("ADC raw = %i \t ADC averaged = %i \t ADC map = %i \n", analogRead(potPin), analogValue, mapVal);

}
