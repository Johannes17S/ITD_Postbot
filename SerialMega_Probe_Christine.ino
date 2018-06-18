

int zahl1=1;
int zahl2;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 Serial1.begin(9600);
 
}

void loop() {
 
    Serial1.println(zahl1);
    delay(1000);

    zahl2 = Serial1.read();
    Serial.println(zahl2);

}
