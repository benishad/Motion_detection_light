//우웅 우웅 반복 소리 코드
#include "Volume.h"
Volume vol;
uint16_t frequency = 440;
void setup() {
  vol.begin();
  vol.alternatePin(true);
}
void loop() {
  for(byte volume = 0; volume < 255; volume++){
    vol.tone(frequency,volume);
    vol.delay(5);
  }
  for(byte volume = 255; volume > 0; volume--){
    vol.tone(frequency,volume);
    vol.delay(5);
  }
  vol.noTone();
  vol.delay(1000);
}
