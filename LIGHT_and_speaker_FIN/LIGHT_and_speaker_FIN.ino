#include <SoftwareSerial.h>

//***************************************************************************

#include <Volume.h> // Used for programmatic volume control
#include <JeeLib.h> // Used for deep sleep

Volume vol; // Plug your speaker into the default pin for your board type:
            // https://github.com/connornishijima/arduino-volume1#supported-pins
            
ISR(WDT_vect) { // Jeelib Sleepy uses this to wake back up
  Sleepy::watchdogEvent();
}

const bool demoMode = true; // Use this to test your speaker and hear the sounds at 2sec intervals. Set to false for long sleep mode.

const unsigned int sleepTimes[] PROGMEM = {3, 10, 30, 60, 180}; // These are the random sleep intervals: 3min, 10min, 30min, 1hr, 3hr.

unsigned int sleepMinutes = 0;
// This is used to make the cricket do an initial extended
// sleep if you'd like. use anywhere from 0 to 65,535 minutes (45 days!)
// This is good for hiding the payload inconspicuously. ;)

byte repeat = 0; // Used at random to combine noises
//********************************************************************************************

int PIR = 2;                      //모션인식센서 2번
int State = 0;                              
int LIGHT = 10;                   //전등제어를 위한 릴레이 핀을 10번으로

int delayTime = 1000;             //딜레이 1초
void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, OUTPUT);
  pinMode(PIR, INPUT);
  
  while (sleepMinutes > 0) {
    int sleepTime = 60000;
    Sleepy::loseSomeTime(sleepTime);
    sleepMinutes--;
  }

  vol.begin();

  randomSeed(analogRead(A5));
}

void loop() {
  int val = digitalRead(PIR);      //모션센서 값 변수 설정
  if (val == LOW)                  //모션이 없으면
  {
    Serial.println("on");         
    digitalWrite(LIGHT, HIGH);     //전등 on
    State = 0;
    chirpAndSleep();                //소리on
  } else{                          //모션이 감지되면
    Serial.println("Dectectied");
    digitalWrite(LIGHT, LOW);       //전등 off
   vol.noTone();                    //소리 off
  } 
  delay(delayTime);                //딜레이 위에 설정한 시간
}
//**********************************************************************************************
//                                        아래는 전부 소리 패턴부 소리 간격을 조절하려면 80번줄로
//***********************************************************************************************
void chirpAndSleep() {
  chirp(); // Go decide on a type of noise to make then come back

  int chance = random(1, 10); // 1 in 10 chance of making two or three random noises this cycle
  if (chance == 1) {
    repeat = random(1, 2);
  }

  if (repeat > 0) { // If we're making more than one noise, don't sleep
    repeat--;
  }
  else { // No noises left, time to sleep
    if (demoMode == true) { // If we're in demo mode, don't sleep.
      vol.delay(1000);//********************************************************귀뚜라미 소리 간격 설정
    }
    else { // If not, sleep tight!
      int sleepTime = sleepTimes[random(0, 5)] + random(0, 6); // Get random time from sleepTimes list, and add a random 0-5 minutes.
      // Nighty night
      while (sleepTime > 0) { // sleep one minute at a time
        Sleepy::loseSomeTime(60000);
        sleepTime--;
      }
    }
  }
}

void chirp() {
  int freq = random(3700, 4000); // random frequency in this range is picked for this chirp
  float volume = random(10, 100+1) / 100.00; // random volume between 10-100% is chosen for this chirp

  int chirpType = random(0, 3); // randomly pick a type of noise to make

  if (chirpType == 0) { // Burst chirp
    int chirpCount = random(1, 3);
    int count = random(1, 6);
    while (chirpCount > 0) {
      chirpLoud(count, freq, volume);
      vol.delay(100);
      chirpCount--;
    }
  }
  if (chirpType == 1) { // Faded chirp
    int chirpCount = random(1, 3);
    chirpFade(chirpCount, freq, volume);
  }
  if (chirpType == 2) { // Creepy rustle noise
    int chirpCount = random(1, 3);
    int count = 3;
    while (chirpCount > 0) {
      chirpNoise(count, volume);
      vol.delay(10);
      chirpCount--;
    }
  }
}

void chirpLoud(byte times, int freq, float volume) {
  while (times > 0) {
    int v = 0;
    while (v < 255) {
      vol.tone(freq, v * volume);
      v += 4;
    }
    v = 255;
    while (v > 0) {
      vol.tone(freq, v * volume);
      v -= 4;
    }
    vol.delay(10);
    times--;
  }
  vol.noTone();
}

void chirpFade(byte times, int freq, float volume) {
  float fadeOut = 1.00;
  while (times > 0) {
    float mv = 0;
    while (mv < 1.00) {
      int v = 0;
      while (v < 255) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v += 4;
      }
      v = 255;
      while (v > 0) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v -= 4;
      }
      vol.delay(20);
      mv += 0.2;
    }
    mv = 1.00;
    while (mv > 0.00) {
      int v = 0;
      while (v < 255) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v += 4;
      }
      v = 255;
      while (v > 0) {
        vol.tone(freq, v * volume * mv * fadeOut);
        v -= 4;
      }
      vol.delay(20);
      mv -= 0.2;
    }
    vol.noTone();
    fadeOut -= 0.75;
    times--;
  }
}

void chirpNoise(byte times, float volume) {
  while (times > 0) {
    int v = 0;
    while (v < 128) {
      vol.tone(random(6000, 10000), v * volume);
      v += 4;
    }
    v = 128;
    while (v > 0) {
      vol.tone(random(6000, 10000), v * volume);
      v -= 4;
    }
    vol.delay(10);
    times--;
  }
  vol.noTone();
}
