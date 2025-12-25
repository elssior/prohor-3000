#include <Servo.h>

Servo R;
const int buttonPin = 2;

bool workMode = false;
bool lastBtn = HIGH;

const int homeR = 55;
const int workR = 50;

void setup() {
  unsigned long seed = 0;
  for (int i = 0; i < 32; i++) {
    seed = (seed << 1) ^ analogRead(A0);
    delay(1);
  }
  randomSeed(seed);

  R.attach(8);
  pinMode(buttonPin, INPUT_PULLUP);

  R.write(homeR);
  delay(200);
}

void tap(Servo &s, int angle, int home) {
  int randomTapDelay = random(100, 500);
  s.write(90);
  delay(150);
  s.write(angle);
  delay(150);
  s.write(home);
  delay(randomTapDelay);
}

void multiTap(Servo &s, int angle, int home, int count) {
  for (int i = 0; i < count; i++) {
    tap(s, angle, home);
  }
}

void loop() {
  bool btn = digitalRead(buttonPin);

  // Переключение между начальным и рабочим режимом
  if (lastBtn == HIGH && btn == LOW) {
    workMode = !workMode;
    delay(40);
  }
  lastBtn = btn;

  if (workMode) {
    // Рабочий режим
    int randomDoubleTab = random(0, 1000);
    int randomCommonDelay = random(5000, 15000);

    if (randomDoubleTab >= 900) {
      multiTap(R, workR, homeR, 3);
    } else if (randomDoubleTab >= 800) {
      multiTap(R, workR, homeR, 2);
    } else {
      tap(R, workR, homeR);
    }
    
    delay(randomCommonDelay);
  } else {
    // Начальный режим
    R.write(homeR);
    delay(40);
  }
}