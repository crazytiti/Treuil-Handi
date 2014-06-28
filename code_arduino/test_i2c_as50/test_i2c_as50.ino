#include <Wire.h>
#include <EEPROM.h>
#include "compteur.h"

#define adr_enc1  64
#define adr_eeprom_nb_tour  0

compteur potar(adr_enc1, adr_eeprom_nb_tour);

void setup()
{
  Serial.begin(9600);  // start serial for output
  potar.init();
}

void loop()
{
 float r;
 signed int nb_tour;
 signed int pos, old_pos;
 
 while(1)
 {
  float r;
  r = potar.get_tour();
  Serial.print("\nr:");
  Serial.print(r);
  delay(200);
  }
}


