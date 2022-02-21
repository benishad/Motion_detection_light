int pir = 2;
int led = 10;
int pirState = LOW;               //처음 pir 가동시 움직임 없음으로 시작



void setup() {
  pinMode(pir,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  digitalWrite(led,HIGH);       //처음 led키고 시작하기
}

void loop() {
 int val = digitalRead(pir);      //모션센서 값 변수 설정
// Serial.println(val);           
 
 if(val ==LOW) {                    //모션값이 0이면
  if(pirState ==HIGH){              //pirstate가 1이면 
    digitalWrite(led, HIGH);        //led를 켠다
    Serial.println("Motion ended!");
    pirState = LOW;                  //pirstate 값은 0으로 바꾼다
  }
 }
 else{                                //모션값이 1이면
  if(pirState ==LOW){                 //pirstate값이 0이면
    digitalWrite(led, LOW);           //led를 끈다
    Serial.println("Motion dectectied!");
    pirState = HIGH;                  //pirstate를 1로 바꾼다
  }
 }
}
