#include <Servo.h>

Servo ESC;
int power = 0;

void setup() {
ESC.attach(3);
Serial.begin(9600);
}

void loop() {
Serial.println("Starting Sequence in 5 Seconds");
delay(5000);
power = 2000;
ESC.writeMicroseconds(power);
delay(1500);
ESC.writeMicroseconds(power);
Serial.println("Sequence Completed");
delay(200);
}
