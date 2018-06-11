/*

 * control of arexx robot for human tracking

 */

#include <Wire.h>
 #include<SoftwareSerial.h>


 #define leftf 9
 #define leftb 10
 #define rightf 5
 #define rightb 6





 int32_t panError;
 int speedLeft,speedRight;




void setup() {

  //Setup: Initalization




  Serial.begin(9600);




   

  //pin 9 left foreward

  pinMode(leftf, OUTPUT);

  //pin 10 left backward

  pinMode(leftb, OUTPUT);

  //pin 5 right foreward

  pinMode(rightf, OUTPUT);

  //pin 6 right backward

  pinMode(rightb, OUTPUT);




  

  //Then set the start value of the signals to zero: 

  analogWrite(leftf, 0); //pin 9 to ground  

  analogWrite(leftb, 0);  //pin 10 to ground 

  analogWrite(rightf, 0); //pin 5 to ground 

  analogWrite(rightb, 0); //pin 6 to ground

  //Startup delay:

  delay(2000);




}




void loop() {

  panError = Serial.read();

  Serial.println("panError:" + panError);

  delay(50); 

  map(panError, -159, 159, 0, 1);

  Serial.println(" mapped panError:" + panError);




  speedRight =1*255; 

  speedLeft =1*185;




  //analogWrite(leftb, speedLeft);

  analogWrite(rightb, speedRight);




  delay(500);

 

}
