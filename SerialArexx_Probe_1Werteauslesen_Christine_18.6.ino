#include<Wire.h>
#include<SoftwareSerial.h>

//define numbers to control arexx
#define leftf 9 
#define leftb 10 
#define rightf 5 
#define rightb 3

int speedLeft;    //speed left
int speedRight;   //speed right
int readValue;    //value from Arduino Mega


void setup() {
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
}

void loop() {

     //get the value from the Arduino Mega
     readValue=Serial.read();
     Serial.print(readValue);
     delay(200);
     
      if(readValue==1){           //turn left
         speedRight =1*0;  
         speedLeft =1*200; 
         analogWrite(leftf, speedLeft); 
         analogWrite(rightf, speedRight);
         analogWrite(rightb, 0); //pin 6 to ground
         analogWrite(leftb, 0);  //pin 10 to ground          
        }
     else if(readValue==2){      //turn right
         speedRight =1*200;  
         speedLeft =1*0; 
         analogWrite(leftf, speedLeft); 
         analogWrite(rightf, speedRight);
         analogWrite(rightb, 0); //pin 6 to ground
         analogWrite(leftb, 0);  //pin 10 to ground      
       }
     else if(readValue==3){      //turn forward
         speedRight =1*255;  
         speedLeft =1*255; 
         analogWrite(leftf, speedLeft); 
         analogWrite(rightf, speedRight);
         analogWrite(rightb, 0); //pin 6 to ground
         analogWrite(leftb, 0);  //pin 10 to ground 
       } 
     else if(readValue==4){      //turn backward
         speedRight =1*200;  
         speedLeft =1*200; 
         analogWrite(leftb, speedLeft); 
         analogWrite(rightb, speedRight); 
         analogWrite(leftf, 0);  //pin 9 to ground     
         analogWrite(rightf, 0); //pin 5 to ground     
       }
     else if(readValue==5){      //brake
         analogWrite(leftf, 0);  //pin 9 to ground     
         analogWrite(rightf, 0); //pin 5 to ground  
         analogWrite(rightb, 0); //pin 6 to ground
         analogWrite(leftb, 0);  //pin 10 to ground      
       }
}
