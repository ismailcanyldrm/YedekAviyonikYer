#include "LoRa_E22.h"
#include <SoftwareSerial.h>

SoftwareSerial lora(11,10);
LoRa_E22 E22(&lora);
 
struct Signal {
    byte Xgyro[4];
    byte Ygyro[4];
    byte Zgyro[4];
    byte Xivme[4];
    byte Yivme[4];
    byte Zivme[4];
    byte h[4];
    byte p[4];
    byte gpsE[4];
    byte gpsB[4];
    byte gpsH[4];
    byte gpsS[4];
    byte T1[4];
    byte T2[4];
} data;

void setup() {  
  Serial.begin(9600);
  E22.begin(); 
  pinMode(13,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(13, HIGH);
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}
void loop() {
    while (E22.available() > 1) {
    ResponseStructContainer rsc = E22.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    rsc.close();

    Serial.print(*(float*)(data.Xgyro),2);  Serial.print("*");
    Serial.print(*(float*)(data.Ygyro),2);  Serial.print("*");
    Serial.print(*(float*)(data.Zgyro),2);  Serial.print("*");

    Serial.print(*(float*)(data.Xivme),2);  Serial.print("*");
    Serial.print(*(float*)(data.Yivme),2);  Serial.print("*");
    Serial.print(*(float*)(data.Zivme),2);  Serial.print("*");

    Serial.print(*(float*)(data.h),2);      Serial.print("*");
    Serial.print(*(float*)(data.p),2);      Serial.print("*"); 

    Serial.print(*(float*)(data.gpsE),6);   Serial.print("*");
    Serial.print(*(float*)(data.gpsB),6);   Serial.print("*");
    Serial.print(*(float*)(data.gpsH),2);   Serial.print("*");
    Serial.print(*(float*)(data.gpsS),2);   Serial.println("*");
 //  Serial.print(*(float*)(data.T1),2);   Serial.print("*");
 //   Serial.print(*(float*)(data.T2),2);   Serial.println("*");
    }   
}
