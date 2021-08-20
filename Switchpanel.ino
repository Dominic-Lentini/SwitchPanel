#include <Joystick.h>

void rd2Way(byte input, int k);
void rd3WayShft(byte input);
void rd3Way(int pin1, int pin2, int k);
Joystick_ Joystick;//(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 64, 0, true, true, false, false, false, false, false, false, false, false, false);
int load = 16;
int load2 = 15;
int load3 = 14;
int clockEnablePin = 4;
int clockEnablePin2 = 3;
int clockEnablePin3 = 2;
int dataIn1 = 6;
int dataIn2 = 7;
int dataIn3 = 8;
int clockIn = 5;

int xAxis = 0;
int yAxis = 0;
int zAxis = 0;
void setup() {
  Joystick.setXAxisRange(0, 255);
  Joystick.setYAxisRange(0, 255);
  Joystick.setZAxisRange(0, 255);
  Joystick.begin();
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(load2, OUTPUT);
  pinMode(clockEnablePin2, OUTPUT);
  pinMode(load3, OUTPUT);
  pinMode(clockEnablePin3, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn1, INPUT);
  pinMode(dataIn2, INPUT);
  pinMode(dataIn2, INPUT);
  pinMode(dataIn3, INPUT);
 // pinMode(0,INPUT);
 // pinMode(1,INPUT);

}
void loop() {
  xAxis = map(analogRead(A0),0,1023,0,255);
  yAxis = map(analogRead(A1),0,1023,0,255);
  zAxis = map(analogRead(A2),0,1023,0,255);
  Joystick.setXAxis(xAxis);
  Joystick.setYAxis(yAxis);
  Joystick.setZAxis(zAxis);
  digitalWrite(load, LOW);
  digitalWrite(load2, LOW);
  digitalWrite(load3, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  digitalWrite(load2, HIGH);
  digitalWrite(load3, HIGH);
  delayMicroseconds(5);
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte in1 = shiftIn(dataIn1, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);
  digitalWrite(clockIn, LOW);
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin2, LOW);
  byte in2 = shiftIn(dataIn2, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin2, HIGH);
  digitalWrite(clockIn, LOW);
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin3, LOW);
  byte in3 = shiftIn(dataIn3, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin3, HIGH);
  rd2Way(in1,0);
  rd2Way(in2,16);
  rd2Way(in3,32);
  rd3Way(0,1,48);
  rd3Way(9,10,51);
  

delay(5);
}

void rd2Way(byte input, int k){
  
  int k1=k;
  for(int i = 0; i<8; i++){  
  if(bitRead(input,i)==1){
    Joystick.releaseButton(k1);
    Joystick.pressButton(k1+1);
  }
  if(bitRead(input,i)==0){
    Joystick.releaseButton(k1+1);
    Joystick.pressButton(k1);
  }

  k1+=2;

}
}

void rd3WayShft(byte input, int k){
  int k1=k;
  for(int i = 0; i < 8;i+=2){
  if(bitRead(input, i)==1){
    Joystick.releaseButton(k+1);
    Joystick.releaseButton(k+2);
    Joystick.pressButton(k);
  }
  if(bitRead(input,i)==0){
    Joystick.releaseButton(k+2);
    Joystick.releaseButton(k);
    Joystick.pressButton(k+1);
  }
  if(bitRead(input,i+1)==1){
    Joystick.releaseButton(k);
    Joystick.releaseButton(k+1);
    Joystick.pressButton(k+2);
  }
  k1+=3;
}
}

void rd3Way(int pin1, int pin2, int k){
  if(digitalRead(pin1) == 1){
    Joystick.releaseButton(k+2);
    Joystick.releaseButton(k+1);
    Joystick.pressButton(k);
  }
  if(digitalRead(pin2) == 1){
    Joystick.releaseButton(k);
    Joystick.releaseButton(k+1);
    Joystick.pressButton(k+2);
  }
  if(digitalRead(pin1) == 0 && digitalRead(pin2) == 0){
    Joystick.releaseButton(k);
    Joystick.releaseButton(k+2);
    Joystick.pressButton(k+1);
  }
}
