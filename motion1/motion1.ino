int pir = 2;
int led = 13;

void setup() {
  pinMode(pir,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 int val = digitalRead(pir);
 Serial.println(val);

 if(val ==HIGH) {
  digitalWrite(led, HIGH);
 }
 else{
  digitalWrite(led, LOW);
 }
}
