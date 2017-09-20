#include "nRF24L01.h"
#include "RF24.h"
#include <SPI.h>

const int CE_pin = 7;
const int CS_pin = 53;

RF24 radio(CE_pin,CS_pin);
const uint64_t pipe = 0xF0F0F0F0E1LL;

typedef struct{
  int W;
  int X;
  float Y;
  float Z;
  char texto[13] = "Ola mundo!!!";
  char texto2[7] = "abcdefg";
}
B_t;

B_t duino2;

void setup(void){
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  duino2.W = 10;
  duino2.X = 20;
  duino2.Y = 10.00;
  duino2.Z = 11.00;

  Serial.println(sizeof(duino2));
  Serial.println();
  
  bool ok = radio.write(&duino2, sizeof(duino2));

  if(ok)
    Serial.println(F("OK"));
  else
    Serial.println(F("Falha"));
}
