/* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////Final/////////////////////////////////////////////////////////////////////////////
*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int buttonPin_1       = 20;
const unsigned long SEND_INTERVAL = 75;  // ms
unsigned long lastSendTime  = 0;

#define VRX_PIN 4
#define VRY_PIN 5

int actualCenterX;
int actualCenterY;
const int ANALOG_DEADZONE_RADIUS = 40;  // tune this

char messageBuffer[32];

void setup() {
  pinMode(buttonPin_1, INPUT_PULLUP);
  Serial.begin(9600);

  // Calibrate joystick center (do NOT touch it!)
  delay(500);
  long sumX = 0, sumY = 0;
  for (int i = 0; i < 100; i++) {
    sumX += analogRead(VRX_PIN);
    sumY += analogRead(VRY_PIN);
    delay(20);
  }
  actualCenterX = sumX / 100;
  actualCenterY = sumY / 100;
}

void loop() {
  unsigned long now = millis();
  if (now - lastSendTime < SEND_INTERVAL) return;
  lastSendTime = now;

  int rawX = analogRead(VRX_PIN);
  int rawY = analogRead(VRY_PIN);
  int buttonState = (digitalRead(buttonPin_1) == LOW) ? 1 : 0;

  int processedX = 0;
  int processedY = 0;

  // X axis
  int dx = rawX - actualCenterX;
  if (abs(dx) > ANALOG_DEADZONE_RADIUS) {
    if (dx < 0) {
      // left: map 0 → (centerX-Δ) to -100 → 0
      processedX = map(
        rawX,
        0,
        actualCenterX - ANALOG_DEADZONE_RADIUS,
        -100,
        0
      );
    } else {
      // right: map (centerX+Δ) → 4095 to 0 → 100
      processedX = map(
        rawX,
        actualCenterX + ANALOG_DEADZONE_RADIUS,
        4095,
        0,
        100
      );
    }
    processedX = constrain(processedX, -100, 100);
  }

  // Y axis
  int dy = rawY - actualCenterY;
  if (abs(dy) > ANALOG_DEADZONE_RADIUS) {
    if (dy < 0) {
      // down: map 0 → (centerY-Δ) to -100 → 0
      processedY = map(
        rawY,
        0,
        actualCenterY - ANALOG_DEADZONE_RADIUS,
        -100,
        0
      );
    } else {
      // up: map (centerY+Δ) → 4095 to 0 → 100
      processedY = map(
        rawY,
        actualCenterY + ANALOG_DEADZONE_RADIUS,
        4095,
        0,
        100
      );
    }
    processedY = constrain(processedY, -100, 100);
  }
  // Build and send one message: "X,Y|B"
  sprintf(messageBuffer, "%d,%d|%d", processedX, processedY, buttonState);
  Serial.println(messageBuffer);
}
