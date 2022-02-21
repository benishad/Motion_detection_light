#include "Volume3.h"
#define speakerPin 9                          //스피커핀 9번핀

int RED = 6;                                  // 빨간색 초록색 파란색 각각 6,5,11번 핀
int GREEN = 5;
int BLUE = 11;

int PIR = 4;                                  //모션감지센서 2번핀
int State = 0;                                //state를 0으로 초기화

int delayTime = 10;                           //50번째 줄 딜레이 값 설정
int brightness = 0;                           //밝기를 0으로 설정
int fadeAmount = 1;                           //해상도를 1로 설정

unsigned long previousMillis = 1;             //previousMillis를 1로 설정
unsigned long previousMillis2 = 1;            //previousMillis2를 1로 설정

const long deTime = 150 * random(1, 20);      //딜레이 시간설정 = 1에서 20까지 랜덤으로 나온 수에 150을 곱한 수
const long deTime2 = 10;                      //딜레이를 10으로 설정

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = digitalRead(PIR);                          //모션센서 값 변수 설정

  if (val == LOW)                                     //값이 low 모션이 없을때
  {
    unsigned long currentMillis = millis();               //millis현재 가동된 시간을 currentMillis로 설정
  if(currentMillis - previousMillis >= deTime)            //currentMillis와 previousMillis를 뺀 값이 deTime을 넘어서면
  {
    previousMillis = currentMillis;                       //이전시간을 현재시간으로 변경
    chirpFade();                                          //소리를 실행
  }
    Serial.println("on");
    State = 0;                                            //
    blinkLED();                                           //led를 실행
    
  } else {                                                //모션이 감지되면
    Serial.println("Detected");
    vol.noTone();                                         //소리를 멈춤
    noLED();                                              //led도 중지
  }
  delay(delayTime);                                      //딜레이 위에 설정된 값
}

void blinkLED() { // 255, 255, 0
  //딜레이 함수를 쓰지 않고 led를 제어
  unsigned long currentMillis2 = millis();
  if(currentMillis2 - previousMillis2 >= 50)
  {
    previousMillis2 = currentMillis2;
    analogWrite(RED, brightness);
  analogWrite(GREEN, brightness);
  analogWrite(BLUE, 0);

  brightness = brightness + fadeAmount;                     //밝기를 = 밝기 + 해상도

  if (brightness <= 0 || brightness >= 80) {                //밝기가 80이 될때까지 1씩 올림 최대 255 다만 127~255까지 밝기 거의 차이가 없음 눈으로 식별 불가능
    fadeAmount = -fadeAmount;                               //최대로 올라간후에 해상도를 1씩 낮춤 밝기가 낮아짐
  }
  }
}

void noLED() {                                            //led 끄는 함수
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}
//****************************************************************volume라이브러리 예제를 가져왔습니다. 수정하는것은 비추천합니다.
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
