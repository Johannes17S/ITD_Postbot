int trigger=7; 
int echo=8;             
long dauer=0;         
long entfernung=0;   

void setup()
{                              
Serial.begin (9600);          
pinMode(trigger, OUTPUT);     //Ultrasonic
pinMode(echo, INPUT);        
                            //Setup: Initialisierung
pinMode(9, OUTPUT);        //links vorwärts
pinMode(10, OUTPUT);      //links rückwärts
pinMode(5, OUTPUT);      //rechts vorwärts
pinMode(6, OUTPUT);     //rechts rückwärts

//Startwerte der Signale auf Null setzen:
//digitalWrite(9, 0); //set pin 9 to ground
analogWrite(5, 0);
analogWrite(10, 0);
digitalWrite(6, 0);
delay(2000);       
}

void loop()
{
digitalWrite(trigger, LOW);         
delay(5);                                   
digitalWrite(trigger, HIGH);               
delay(10);
digitalWrite(trigger, LOW);
dauer = pulseIn(echo, HIGH);              
entfernung = (dauer/2) * 0.03432;   //Berechnung der Entfernung in Zentimetern(Dividiert durch zwei, da nur eine Strecke berechnet wird und nich hin- und zurück, danach Multiplikation des Wertes mit der Schallgeschwindigkeit in der Einheit Zentimeter/Mikrosekunde)

if (entfernung >= 10 || entfernung <= 0) 
{
Serial.println("Motoren stoppen");  

digitalWrite(10,LOW); digitalWrite(9,LOW); 
digitalWrite(6,LOW); digitalWrite(5,LOW); 

//Beispiel nach rechts drehen:   
//delay(10); 
//digitalWrite(6,LOW); analogWrite(5,200); 
//digitalWrite(10,LOW); digitalWrite(9,LOW); 
//delay(500); 
//digitalWrite(6,LOW); digitalWrite(5,LOW); 
//digitalWrite(10,LOW); digitalWrite(9,LOW);
}

else 
{
Serial.print(entfernung); 
Serial.println(" cm");

digitalWrite(10,LOW); analogWrite(9,200); //pin 10 to ground 
digitalWrite(5,LOW); analogWrite(6,200); //pin 6 to ground
//delay(500);                             
}
delay(1000); 
}
