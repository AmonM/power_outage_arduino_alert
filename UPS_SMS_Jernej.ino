#include <SoftwareSerial.h>

#define PIN 7
SoftwareSerial sms(2, 3); // RX, TX

int off = 0;
int on = 0;

void setup() {
  pinMode(PIN,INPUT);
  Serial.begin(9600);// initialize serial monitor
  pinMode(13,OUTPUT);
}

void loop() {
  int a = digitalRead(PIN);
  if(a){
    if(on < 6){
      on++;
    }
    if(on > 2){
      off = 0;
    }
    if(on == 4){
      //Serial.println("Prikljucen!");
      sendSMS("Napajanje je aktivno!");
      digitalWrite(13, HIGH);
      off = 0;
    }
  }else{
    if(off < 100){
      off++;
    }
    if(off == 99){
      //Serial.println("Izključeno");
      sendSMS("Napajanje ni aktivno!");
      digitalWrite(13, LOW);
      on = 0;
    }
  }
  delay(200);
}

void sendSMS(String text){
  sms.begin(9600);
  sms.print("AT+CMGF=1\r\n");
  String abc = sms.readString();
  Serial.println(abc);
  delay(500);
  sms.print("AT+CMGS=\"+38641824545\"\r\n");
  delay(300);
  sms.print(text);
  sms.write(26);
  abc = sms.readString();
  Serial.println(abc);
}
