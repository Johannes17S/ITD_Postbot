/*
 * control of arexx robot for human tracking
 */
#include <Wire.h>

#define leftf 9
#define rightf 5

int32_t panError; 
int speedLeft,speedRight;

void setup() {
  //Setup: Initalization

  Wire.begin(2);
  Serial.begin(115200);
   
  //pin 9 left foreward
  pinMode(leftf, OUTPUT);
  //pin 10 left backward
  pinMode(10, OUTPUT);
  //pin 5 right foreward
  pinMode(rightf, OUTPUT);
  //pin 6 right backward
  pinMode(6, OUTPUT);

  
  //Then set the start value of the signals to zero: 
  //digitalWrite(leftf, 0); //pin 9 to ground  
  analogWrite(10, 0);   
  analogWrite(rightf, 0);   
  digitalWrite(6, 0); //pin 6 to ground
  //Startup delay:
  delay(2000);

}

void loop() {
  panError = Wire.read();
  Serial.println("panError:" + panError); 
  map(panError, -159, 159, 0, 1);
  Serial.println(" mapped panError:" + panError);

  speedRight = panError*200; 
  speedLeft = (1-panError)*200;

  analogWrite(leftf, speedLeft);
  analogWrite(rightf, speedRight);

  delay(10);
 
}
