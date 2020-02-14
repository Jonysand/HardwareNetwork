#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);//RX,TX

String mesFromServer;
int colorDataIndex = 0;

// RGB config
int Rpin = 3;
int Gpin = 2;
int Bpin = 4;

void setup() {
  pinMode(Rpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  digitalWrite(Rpin, LOW);
  digitalWrite(Gpin, LOW);
  digitalWrite(Bpin, LOW);
  Serial.begin(9600);
  mySerial.begin(115200);
  delay(2000);
  mySerial.println("AT+CWMODE=1");
  while(mySerial.readString().indexOf("OK")==-1){}
  mySerial.flush();
  mySerial.println("AT+CWJAP=\"sandbox370\",\"+s0a+s03!2gether?\"");
  while(mySerial.readString().indexOf("OK")==-1){}
  Serial.println("WiFi connected");
  mySerial.flush();
  mySerial.println("AT+CIPMUX=1");
  while(mySerial.readString().indexOf("OK")==-1){}
  mySerial.flush();
  mySerial.println("AT+CIPSERVER=1,10000");
  while(mySerial.readString().indexOf("OK")==-1){}
  Serial.println("server established");
  mySerial.flush();
  Serial.flush();
}  
 
void loop() {
    // listen for user input and send it to the ESP8266
    if ( Serial.available() ){
      mySerial.write( Serial.read() );
    }
    
    // listen for communication from the ESP8266 and then write it to the serial monitor
    if ( mySerial.available() ){
      mesFromServer = mySerial.readString();
      colorDataIndex = mesFromServer.indexOf("+IPD");
      if(colorDataIndex!=-1){
        setColor(mesFromServer, mesFromServer.indexOf(":")+1);
      }
      Serial.print(mesFromServer);
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
