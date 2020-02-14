#include <SoftwareSerial.h>

SoftwareSerial mySerial(0,1);//RX,TX

String mesFromServer;
int colorDataIndex = 0;

// RGB config
int Rpin = 2;
int Gpin = 4;
int Bpin = 3;

void setup() {
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  mySerial.begin(115200);
  delay(5000);
  mySerial.println("AT+CWMODE=3");
  delay(5000);
  mySerial.flush();
  digitalWrite(Rpin, HIGH);
  digitalWrite(Gpin, HIGH);
  digitalWrite(Bpin, HIGH);
  mySerial.println("AT+RST");
  delay(5000);
  mySerial.flush();
  digitalWrite(Rpin, HIGH);
  digitalWrite(Gpin, LOW);
  digitalWrite(Bpin, LOW);
  mySerial.println("AT+CWJAP=\"sandbox370\",\"+s0a+s03!2gether?\"");
  delay(5000);
  mySerial.flush();
  digitalWrite(Rpin, LOW);
  digitalWrite(Gpin, HIGH);
  digitalWrite(Bpin, LOW);
  mySerial.println("AT+CIPMUX=1");
  delay(5000);
  mySerial.flush();
  digitalWrite(Rpin, LOW);
  digitalWrite(Gpin, LOW);
  digitalWrite(Bpin, HIGH);
  mySerial.println("AT+CIPSERVER=1,10000");
//  mySerial.println("AT+CIPSTART=\"TCP\",\"10.18.111.85\",10000");
  delay(5000);
  mySerial.flush();
  digitalWrite(Rpin, HIGH);
  digitalWrite(Gpin, HIGH);
  digitalWrite(Bpin, HIGH);
}  
 
void loop() {
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() ){
      mesFromServer = mySerial.readString();
      colorDataIndex = mesFromServer.indexOf("+IPD");
      if(colorDataIndex!=-1){
//        setColor(mesFromServer, mesFromServer.indexOf(":")+1);
  digitalWrite(Rpin, HIGH);
    digitalWrite(Gpin, LOW);
    digitalWrite(Bpin, LOW);
      }
    }
}

void setColor(String mes, int idx) {
  if (mes.substring(idx,idx+1).toInt()==1) 
    digitalWrite(Rpin, HIGH);
  else
    digitalWrite(Rpin, LOW);
  if (mes.substring(idx+1,idx+2).toInt()==1) 
    digitalWrite(Gpin, HIGH);
  else
    digitalWrite(Gpin, LOW);
  if (mes.substring(idx+2,idx+3).toInt()==1) 
    digitalWrite(Bpin, HIGH);
  else
    digitalWrite(Bpin, LOW);
}
