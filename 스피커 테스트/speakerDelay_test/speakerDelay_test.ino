#include "Volume3.h"
#define speakerPin 9

int RED = 6;
int GREEN = 5;
int BLUE = 11;

int PIR = 2;
int State = 0;

int delayTime = 10;
int brightness = 0;
int fadeAmount = 1;

unsigned long previousMillis = 1;
unsigned long previousMillis2 = 1;
unsigned long previousMillis3 = 0;

const long deTime = 150 * random(1, 20);
const long deTime2 = 10;
const long deTime3 = 1;

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(PIR);      //모션센서 값 변수 설정

  if (val == LOW)
  {
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= deTime)
  {
    previousMillis = currentMillis;
    chirpFade();
  }
    Serial.println("on");
    State = 0;
    blinkLED();
    
  } else {
    Serial.println("no");
    vol.noTone();
    noLED();
  }
  delay(delayTime);
}

void blinkLED() { // 255, 255, 0
  
  unsigned long currentMillis2 = millis();
  if(currentMillis2 - previousMillis2 >= 50)
  {
    previousMillis2 = currentMillis2;
    analogWrite(RED, brightness);
  analogWrite(GREEN, brightness);
  analogWrite(BLUE, 0);

  brightness = brightness + fadeAmount;

  if (brightness <= 0 || brightness >= 80) {
    fadeAmount = -fadeAmount;
  }
  }
}

void noLED() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
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
}

void counttime(){
  unsigned long currentMillis2 = millis();
  if(currentMillis2 - previousMillis2 >= deTime2)
  {
    previousMillis2 = currentMillis2;
  }
}
