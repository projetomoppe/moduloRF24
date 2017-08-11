#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int SW1 = 7;

void setup(void){
  Serial.begin(57600);
  radio.begin();
  radio.openWritingPipe(pipe);
}

void loop(void)
{
  if (digitalRead(SW1) == HIGH)
  {
    struct comRF {
      int msg = 0;
      int msg2 = 1;
      char texto[8] = "S1";
    } dadosEnvio;
   
    radio.write(&dadosEnvio, sizeof(dadosEnvio));

    Serial.println("--------------------");
    Serial.println(dadosEnvio.msg);
    Serial.println(dadosEnvio.msg2);
    Serial.println(dadosEnvio.texto);
    Serial.println();
  }
  else
  {
    struct comRF {
      int msg = 2;
      int msg2 = 3;
      char texto[8] = "S2";
    } dadosEnvio;
    
    radio.write(&dadosEnvio, sizeof(dadosEnvio));

    Serial.println("--------------------");
    Serial.println(dadosEnvio.msg);
    Serial.println(dadosEnvio.msg2);
    Serial.println(dadosEnvio.texto);
    Serial.println();
  }
}
