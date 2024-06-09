#include <Arduino.h>
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
  pinMode(6, INPUT);
  pinMode(3, OUTPUT);
  pinMode(1, INPUT);//key2
  pinMode(0, INPUT);//key1
  key_1_last=0;
  key_1_now=0;
  pin_6_last=0;
  pin_6_now=0;
  zero_crossing_flag=0;
}

void loop() {
  pin_6_last=pin_6_now;
  pin_6_now=digitalRead(6);

  if(pin_6_last==LOW&&pin_6_now==HIGH){
    zero_crossing_flag=1;
  }
  if(zero_crossing_flag){
    key_1_last=key_1_now;
    key_1_now=digitalRead(0);
    if(key_1_last==LOW&&key_1_now==HIGH){
      alpha=alpha+10;
      if(alpha>179) alpha=alpha%179;
    } 
    SETanlge(alpha);
    zero_crossing();
    zero_crossing_flag=0;
  }
}