#include <Arduino.h>
#define ALPHAMIN 5
#define ALPHAMAX 175

bool key_1_now;
bool key_1_last;
bool pin_6_now;
bool pin_6_last;
bool zero_crossing_flag;
int Talpha;
int alpha;

int SETanlge(int angle){
  Talpha=10000*angle/180;//in us
  return Talpha;
}

void zero_crossing(){
    delayMicroseconds(Talpha);
    digitalWrite(3,HIGH);
    delayMicroseconds(10);
    digitalWrite(3,LOW);
}
void setup() {
  pinMode(14, OUTPUT);//LED
  pinMode(9, INPUT);
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  pinMode(1, INPUT);//key2
  pinMode(0, INPUT);//key1
  key_1_last=0;
  key_1_now=0;
  alpha=90;
  SETanlge(alpha);
}

void loop() {
  key_1_last=key_1_now;
  key_1_now=digitalRead(0);
  if(key_1_last==LOW&&key_1_now==HIGH){
      alpha=alpha+10;
      if(alpha>ALPHAMAX) alpha=alpha%ALPHAMAX+ALPHAMIN;
      SETanlge(alpha);
    } 
  delay(10);
}