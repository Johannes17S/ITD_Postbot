//Hochschule Hamm Lippstadt
//Christine Agethen
   
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

int maxArea=1000;     //max. area of the recognized object
int minArea=600;      //min. area of the recognized object
int Xmin=120;         //min value of the center of the recognized object
int Xmax=200;         //max value of the center of the recognized object 

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.print("Starting...\n");
 
  pixy.init();
}

void loop()
{ 
  static int i = 0;
  uint16_t blocks;
  //blocks = pixy.getBlocks();               //receive data from pixy

  signature = pixy.blocks[i].signature;    //get object's signature
  x = pixy.blocks[i].x;                    //get x position
  y = pixy.blocks[i].y;                    //get y position
  width = pixy.blocks[i].width;            //get width
  height = pixy.blocks[i].height;          //get height
  
  char buf[32];
  int j;
  
  // grab blocks!
  
  if(blocks = pixy.getBlocks()){          //receive data from pixy
  
    if(signature == 1){
 
      area = width * height;    //calculate the object area

      //rotate left if x position > Xmax position
      if (x > Xmax){
        int turnLeft=1;
        Serial1.print(turnLeft);
        Serial.println("turnLeft");
      }
     
      //rotate right if x position < Xmin position
      else if (x < Xmin){
        int turnRight=2;
        Serial1.print(turnRight);
        Serial.println("turnRight");
      }

      //drive forward if the object is to small
      else if (area < minArea){
        int forward=3;
        Serial1.print(forward);
        Serial.println("forward");
      }

      //drive backward if the object is to big
      else if (area > maxArea){
        int backward=4;
        Serial1.print(backward);
        Serial.println("backward");
      }

      //else brake
      else /*(x>Xmin && x<Xmax && area>minArea && area<maxArea)*/{
        int brake=5;
        Serial1.print(brake);
        Serial.println("brake");
      } 
      //Serial.println(area);
      //Serial1.println(area);
      delay(1000);
      int aa=Serial1.read();
      Serial.print(aa);
    }
    else{
      int brake=5;
      Serial1.print(brake);
      Serial.print("brake");  
    }
  }
  
}
  

