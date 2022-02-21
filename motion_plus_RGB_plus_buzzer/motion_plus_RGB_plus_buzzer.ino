int RED = 9;                      //rgb led 각각 9,10,11 번 핀
int GREEN = 10;
int BLUE = 11;

int Buzz = 5;

int rgbON = 0;

int Pir = 2;                      //모션인식센서 2번

int pirState = LOW;               //처음 pir 가동시 움직임 초기화
int val = 0;


void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(Buzz, OUTPUT);
  pinMode(Pir,INPUT);

  Serial.begin(9600);

}

void loop() {

 val = digitalRead(Pir);      //모션센서 값 변수 설정
// Serial.println(val);           

if(val ==LOW) {
  if(pirState ==HIGH){
    rgbON = 1;
    tone(Buzz, HIGH);        
    Serial.println("Motion ended!");
    pirState = LOW;
  }
 }
 else{
  if(pirState ==LOW){
    rgbON = 0;
    noTone(Buzz);
    Serial.println("Motion dectectied!");
    pirState = HIGH;
  }
 }

 if(rgbON==1){
  rgb(50, 0, 0);                           //빨간불만 들어오게하기 밝기 0~255의 밝기
  delay(100);

  rgb(0, 50, 0);                           //초록불만 들어오게하기 밝기 0~255의 밝기
  delay(100);
  
  rgb(0, 0, 50);                           //파란불만 들어오게하기 밝기 0~255의 밝기
  delay(100);
 }
 else{
  rgb(0, 0, 0);
  delay(100);
 }
 
}

void rgb(int R, int G, int B){
  analogWrite(RED, R);
  analogWrite(GREEN, G);
  analogWrite(BLUE, B);
}
