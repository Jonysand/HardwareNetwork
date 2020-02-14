int Rpin = 3;
int Gpin = 2;
int Bpin = 4;
int rValue = 0;
int gValue = 0;
int bValue = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);

  analogWrite(Rpin, 128);
  analogWrite(Gpin, 255);
  analogWrite(Bpin, 72);
}

void loop() {
  // put your main code here, to run repeatedly:
//  delay(1000)
  rValue++;
  gValue+=2;
  bValue+=3;
  if (rValue>=255) rValue = 0;
  if (gValue>=255) gValue = 0;
  if (bValue>=255) bValue = 0;
  analogWrite(Rpin, rValue);
  analogWrite(Gpin, gValue);
  analogWrite(Bpin, bValue);
}
