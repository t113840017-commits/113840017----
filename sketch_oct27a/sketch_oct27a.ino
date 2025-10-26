const int buttonPin = 2;
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

unsigned long lastPressTime = 0;
const unsigned long idleTime = 2000; // 閒置 2 秒轉紅
const int fadeDelay = 5;              // 漸變速度
const int debounceDelay = 50;         // 按鈕防彈跳時間

bool isRed = false;          // 當前狀態
bool lastButtonState = HIGH; // 上一次按鈕狀態
unsigned long lastDebounceTime = 0;   // 上次按鈕變化時間

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  setColor(0, 0, 255); // 開機時藍色
}

void loop() {
  int reading = digitalRead(buttonPin);
  unsigned long now = millis();

  // 防彈跳處理
  if (reading != lastButtonState) {
    lastDebounceTime = now;
  }

  if ((now - lastDebounceTime) > debounceDelay) {
    // 按鈕穩定變化後再處理
    if (reading == LOW) { // 偵測到按下
      lastPressTime = now;

      if (isRed) {
        fadeRedToBlue();  // 紅 → 藍
        isRed = false;
      } else {
        setColor(0, 0, 255); // 已是藍 → 保持藍
      }
    }
  }

  // 閒置超過 2 秒 → 藍 → 紅
  if ((now - lastPressTime > idleTime) && !isRed) {
    fadeBlueToRed();
    isRed = true;
  }

  lastButtonState = reading;
}

// 🔵 → 🔴
void fadeBlueToRed() {
  for (int i = 0; i <= 255; i++) {
    int redValue = i;
    int blueValue = 255 - i;
    setColor(redValue, 0, blueValue);
    delay(fadeDelay);
  }
}

// 🔴 → 🔵
void fadeRedToBlue() {
  for (int i = 0; i <= 255; i++) {
    int redValue = 255 - i;
    int blueValue = i;
    setColor(redValue, 0, blueValue);
    delay(fadeDelay);
  }
}

// 共陽極反轉
void setColor(int r, int g, int b) {
  analogWrite(redPin, 255 - r);
  analogWrite(greenPin, 255 - g);
  analogWrite(bluePin, 255 - b);
}










