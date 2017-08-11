#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

struct comRF {
  int msg;
  int msg2;
  char texto[8] = {0};
};

RF24 radio(9, 10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

struct comRF dadosRecebe;

void setup(void) {
  Serial.begin(57600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(void)
{ 
  if (radio.available())
  {   
    bool done = false;
    while (!done)
    { 
      done = radio.read(&dadosRecebe, sizeof(dadosRecebe));

      Serial.println("--------------------");
      Serial.println(dadosRecebe.msg);
      Serial.println(dadosRecebe.msg2);
      Serial.println(dadosRecebe.texto);
      Serial.println();

      //done = radio.read(msg, 1);
      //      if(dadosRecebe.msg[0] == 1)
      //      {
      //        Serial.println("AAAAA");
      //        digitalWrite(LED_BUILTIN, HIGH);
      //      }
      //      else
      //      {
      //        digitalWrite(LED_BUILTIN, LOW);
      //      }
    }
  }
  //  else
  //  {
  //    Serial.println("No radio available");
  //  }
}
