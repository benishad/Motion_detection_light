#include <SoftwareSerial.h>

int RED = 9;                      //rgb led 각각 9,10,11 번 핀
int GREEN = 10;
int BLUE = 11;

int BUZZER = 5;
int PIR = 2;                      //모션인식센서 2번
int State = 0;

int delayTime = 10;
int brightness = 0;
int fadeAmount = 1;

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  int val = digitalRead(PIR);      //모션센서 값 변수 설정

  if (val == LOW)
  {
    Serial.println("on");
    State = 0;
    blinkLED();
    tone(BUZZER, 262, 100);
  } else {
    Serial.println("no");
    noTone(BUZZER);
    noLED();
  }
  delay(delayTime);
}

void blinkLED() { // 255, 255, 0
  analogWrite(RED, brightness);
  analogWrite(GREEN, brightness);
  analogWrite(BLUE, 0);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 100) {
    fadeAmount = -fadeAmount;
  }

  delay(50);
}

void noLED() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}
