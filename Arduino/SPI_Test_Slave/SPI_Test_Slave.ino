#include <Servo.h>
#include <SPI.h>

Servo servo;

int pos = 1;
byte buf[100];
volatile byte vals[4];

// SPI Transfer
byte SPItransfer(int value) {
  SPDR = value;
  while (!(SPSR & (1 << SPIF)));
  delay(10);
  return SPDR;
}

void setup() {
  Serial.begin(9600);
  servo.attach(3);
  // Declare MISO as output : have to send on
  //master in, *slave out*
  pinMode(MISO, OUTPUT);
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  // now turn on interrupts
  SPI.attachInterrupt();
  Serial.println("Slave Inititalized");
}

void loop() {
  delay(5);
  servo.write(map(buf[1], 0, 255, 0, 179));
}  // end of loop

// SPI interrupt routine
ISR (SPI_STC_vect) {
  byte q = SPDR;
  
  if (q == '\n') {
    ProcessIt();
    return;
  }
  
  if (pos < sizeof buf) {
    buf[pos++] = q;
    return;
  }
}  // end of interrupt routine SPI_STC_vect

void ProcessIt(void) {
  Serial.println("\nPacket Received");
  Serial.println("<data>");
  for (int i = 1; i < pos; i+=2) {
    Serial.print(buf[i]);
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("</data>");
  pos = 0;
}

