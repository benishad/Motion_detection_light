#include <SoftwareSerial.h>
#include "Volume3.h"
#define speakerPin 9

int RED = 6;                      //rgb led 각각 9,10,11 번 핀
int GREEN = 5;
int BLUE = 11;

//int BUZZER = ;
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
//  pinMode(BUZZER, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  int val = digitalRead(PIR);      //모션센서 값 변수 설정

  if (val == LOW)
  {
    Serial.println("on");
    State = 0;
    blinkLED();
    //sound();
  } else {
    Serial.println("no");
    vol.noTone();
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

void sound() {
  chirpFade();
}

void chirpFade() {
  uint16_t f = 3900;

  uint8_t times = random(1,3);
  float master = 1.0;
  uint16_t v = 0;
  uint8_t vDir = 1;
  float vb = 0;

  while (times > 0) {
    while (vb < 1.0) {
      if (v < 1023 && vDir == 1) {
        v += 16;
      }
      else {
        vDir = 0;
      }

      if (v > 0 && vDir == 0) {
        v -= 16;
      }
      else {
        vDir = 1;
      }

      vol.tone(speakerPin, f, v * constrain(vb, 0.0, 1.0)*master);
      delayMicroseconds(50);
      vb += 0.003;
    }
    while (vb > 0.0) {
      if (v < 1023 && vDir == 1) {
        v += 16;
      }
      else {
        vDir = 0;
      }

      if (v > 0 && vDir == 0) {
        v -= 16;
      }
      else {
        vDir = 1;
      }

      vol.tone(speakerPin, f, v * constrain(vb, 0.0, 1.0)*master);
      delayMicroseconds(50);
      vb -= 0.001;
    }
    times--;
    master -= 0.75;
  }
  vol.noTone();
  delay(random(100,2000));
}
