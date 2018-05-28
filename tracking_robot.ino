/*
 * Sourcecode for tracking tags placed on humans or objects with a robot
 * @author: Johannes Schäfer
 * @institution: Hochschule Hamm-Lippstadt
 */

#include <SPI.h> 
#include <Wire.h> 
#include <Pixy.h>

Pixy pixy;

#define X_CENTER        ((PIXY_MAX_X-PIXY_MIN_X)/2)       

uint16_t blocks;

 static int i = 0;
 int j;
 char buf[32]; 
 int32_t panError; //differnce from image center
 int32_t Width, Height;
 
void setup() {

  
  Serial.begin(9600);
  Serial.print("Starting...\n");

  Wire.begin();
  
  pixy.init();

  if(!SPI.begin)Serial.print("No pixy cam found!");
  else Serial.print("Initialisation successfull!");

}

void loop() 
{
 Wire.beginTransmission(2);
 blockUpdate(); //first aquisition of blocks

 if (blocks)
  {
   panError = X_CENTER-pixy.blocks[0].x;
   Wire.write(panError);
   
    printBuf(); 
  }
 Wire.endTransmission();  
}

void blockUpdate()
{
 blocks = pixy.getBlocks();
}

void printBuf()
{
 // do this (print) every 50 frames because printing every
    // frame would bog down the Arduino
    if (i%50==0) 
    {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);
      for (j=0; j<blocks; j++)
      {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();
      }
    } 
}


