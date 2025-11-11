const int redPin = 3;
const int greenPin = 5;
const int bluePin = 6;
const int buttonPin = 2;

int mode = 0;
bool lastButtonState = HIGH;
bool currentButtonState;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 200;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  checkButton();

  switch (mode) {
    case 0: setColor(0, 0, 0); break; // 預設燈滅
    case 1: blinkColor(255, 0, 0, 500); break; // 紅色閃爍 delay 500
    case 2: blinkColor(255, 0, 255, 300); break; // 紫色閃爍 delay 300
    case 3: setColor(0, 0, 255); break; // 恆亮藍色
    case 4: breathingRainbow(); break; // 呼吸燈變色
    case 5: mode = 0; break; // 回到預設
  }
}

void checkButton() {
  currentButtonState = digitalRead(buttonPin);
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    if (millis() - lastPressTime > debounceDelay) {
      mode++;
      if (mode > 5) mode = 0;
      lastPressTime = millis();
    }
  }
  lastButtonState = currentButtonState;
}

void blinkColor(int r, int g, int b, int delayTime) {
  setColor(r, g, b);
  delay(delayTime);
  setColor(0, 0, 0);
  delay(delayTime);
}

void breathingRainbow() {
  int colors[7][3] = {
    {255, 0, 0}, {255, 127, 0}, {255, 255, 0},
    {0, 255, 0}, {0, 0, 255}, {75, 0, 130}, {148, 0, 211}
  };

  for (int c = 0; c < 7; c++) {
    for (int i = 0; i <= 255; i += 5) {
      analogWrite(redPin, colors[c][0] * i / 255);
      analogWrite(greenPin, colors[c][1] * i / 255);
      analogWrite(bluePin, colors[c][2] * i / 255);
      delay(10);
      checkButton();
      if (mode != 4) return;
    }
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(redPin, colors[c][0] * i / 255);
      analogWrite(greenPin, colors[c][1] * i / 255);
      analogWrite(bluePin, colors[c][2] * i / 255);
      delay(10);
      checkButton();
      if (mode != 4) return;
    }
  }
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
