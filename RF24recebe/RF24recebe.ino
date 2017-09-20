#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

const int CE_pin = 6;
const int CS_pin = 7;
const int LED = LED_BUILTIN;

RF24 radio(CE_pin,CS_pin);
const uint64_t pipe = 0xF0F0F0F0E1LL;

typedef struct{
  int A;
  int B;
  float C;
  float D;
}
A_t;

A_t duino1;

void setup(void){
  Serial.begin(57600);
  pinMode(LED, OUTPUT);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
}

void loop(void)
{
  unsigned long inicio_espera = millis();
  bool timeout = false;

  while(!radio.available() && !timeout) {
    if(millis() - inicio_espera > 250)
      timeout = true;

    if(timeout) {
      Serial.println(F("Falha, timeout"));
      digitalWrite(LED, HIGH);
    }
    else {
      radio.read(&duino1, sizeof(duino1));
      digitalWrite(LED, LOW);
    }

    Serial.print("duino1.A = ");
    Serial.println(duino1.A);
    Serial.print("duino1.B = ");
    Serial.println(duino1.B);
    Serial.print("duino1.C = ");
    Serial.println(duino1.C);
    Serial.print("duino1.D = ");
    Serial.println(duino1.D);
    Serial.println("\r\n");
  }
}
