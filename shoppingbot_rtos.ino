/****************Shoppingbotprojekt******************
Hochschule Hamm Lippstadt
ITD 6. Semester
Autoren: Christine Agethen, Johannes Schäfer

Funktionen müssen sequentiell abgearbeitet werden, da die PixyCam eine 
Nutzung mit FreeRTOS unmöglich macht.
*/
   
#include <SPI.h>  
#include <Pixy.h>

// This is the main Pixy object 
Pixy pixy;

int signature = 0;
int x = 0;            //positon x axis
int y = 0;            //position y axis
int width = 0;        //object's width
int height = 0;       //object's height

int area = 0;         //area of the recognized object

int maxArea=6600;     //max. area of the recognized object
int minArea=300;      //min. area of the recognized object
int Xmin=100;         //min value of the center of the recognized object
int Xmax=220;         //max value of the center of the recognized object 

int trigger=7; 
int echo=8;             
long dauer=0;         
long entfernung=0;

   

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.print("Starting...\n");
  Serial.println("Setting up PixyCam..."); 
  pixy.init();

  Serial.println("Setting up ultrasonic sensors...");     
  pinMode(trigger, OUTPUT);     
  pinMode(echo, INPUT);

  delay(500);
  Serial.println("Setup finished!");

}

void loop()
{
  static int i = 0;
  uint16_t blocks;
  char buf[32];
  int j;

  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
  
  
  // grab blocks!
  
  if(blocks = pixy.getBlocks()){          //receive data from pixy
  
    if(signature == 1){
 
      area = width * height;    //calculate the object area

      //rotate left if x position > Xmax position
      if (x > Xmax){
        turnleft();
      }
     
      //rotate right if x position < Xmin position
      else if (x < Xmin){
        turnright();
      }

      //drive forward if the object is to small
      else if (area < minArea){
        forward();
      }

      //drive backward if the object is to big
      else if (area > maxArea){
        backward();
      }

      //else brake
      else /*(x>Xmin && x<Xmax && area>minArea && area<maxArea)*/{
        brake();
      }
    }
  }
  
 //ultrasonic section
  digitalWrite(trigger, LOW);         
  delay(5); //wait for 5ms                                  
  digitalWrite(trigger, HIGH);               
  delay(10); //wait for 10ms
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);              
  entfernung = (dauer/2) * 0.03432; 

  // brake if any object is closer than 12cm 
 if (entfernung <= 12 && entfernung >= 6) 
 {
  brake();
 }

  // drive backward if any object is closer than 6cm 
 if (entfernung <= 6)
 {
  backward();
 }
}

/**************drive functions********************/
void turnleft()
{
 int turnLeft=1;
 Serial1.write(turnLeft);
 Serial.println("turnLeft");
 //int aa=Serial1.read();
 //Serial.write(aa);
}

void turnright(){
  int turnRight=2;
  Serial1.write(turnRight);
  Serial.println("turnRight");
  //int aa=Serial1.read();
  //Serial.print(aa);
}

void forward(){
 int forward=3;
 Serial1.write(forward);
 Serial.println("forward");
 //int aa=Serial1.read();
 //Serial.write(aa);
}

void backward(){
  int backward=4;
  Serial1.write(backward);
  Serial.println("backward");
  //int aa=Serial1.read();
  //Serial.write(aa);
}

void brake(){
 int brake=5;
 Serial1.write(brake);
 Serial.println("brake");
 //int aa=Serial1.read();
 //Serial.write(aa);
}


