#include <SoftwareSerial.h>

int BUZZER = 5;
int PIR = 2;                      //모션인식센서 2번
int State = 0;
int LIGHT = 10;

int delayTime = 10;

void setup() {
  Serial.begin(9600);
  
  pinMode(LIGHT, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  int val = digitalRead(PIR);      //모션센서 값 변수 설정

  if (val == LOW)
  {
    Serial.println("on");
    digitalWrite(LIGHT, HIGH);
    State = 0;
    tone(BUZZER, 262, 100);
  } else {
    Serial.println("Dectectied");
    digitalWrite(LIGHT, LOW);
    noTone(BUZZER);
  }
  delay(delayTime);
}
