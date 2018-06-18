int number1;
int number2;

void setup() {
  Serial.begin(9600);
}

void loop() {

     number1=Serial.read();
     number2=number1 + 2;
     delay(200);
     Serial.print(number2);
     delay(1000);
    
}
