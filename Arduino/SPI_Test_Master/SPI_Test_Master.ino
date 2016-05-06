#include <SPI.h>
const int b1 = 2;
const int b2 = 3;
const int b3 = 4;
const int potPin = A0;

int vals[4];
int potVal = 0;
char endByte = '\n';
void setup() {
  Serial.begin(9600);
   pinMode(SS, OUTPUT);
  SPI.begin();
  Serial.println("Master Initialized");
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
}

void loop() {
  vals[0] = map(analogRead(potPin), 0, 1023, 0, 255);
  vals[0] = analogRead(potPin);
  vals[1] = digitalRead(b1);
  vals[2] = digitalRead(b2);
  vals[3] = digitalRead(b3);
  if (abs(millis() % 1000) < 100) {
    for (int i = 0; i < 4; i++) {
      dataSend(vals[i]);
    }
    dataSend(endByte);
    Serial.println("\nData Transfered");
  }
  Serial.println("");
  for (int i = 0; i < 4; i++) {
    Serial.print(vals[i]);
    Serial.print(" ");
  }
  delay(50);
}

void dataSend(byte data) {
  digitalWrite(SS, LOW);
  delay(5);
  SPI.transfer(data);
  delay(5);
  int rx = SPI.transfer(potVal);
  //if(rx == potVal){
  //  Serial.println("Slave acknowleged");
  //}
  //else{
  //  Serial.println("Slave didn't acknowlege");
  //}
  digitalWrite(SS, HIGH);
}

