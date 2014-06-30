#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h> 
#include "compteur.h"
#include "moteur.h"

#define button_pin  12
#define moteur_pin  13
#define adr_enc1  64
#define adr_enc2  65
#define adr_eeprom_nb_tour_pot  0
#define adr_eeprom_nb_tour_treuil  4

compteur potar(adr_enc1, adr_eeprom_nb_tour_pot);
compteur treuil(adr_enc2, adr_eeprom_nb_tour_treuil);
moteur moteur_treuil;

void setup()
{
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);  // start serial for output
  potar.init();
  treuil.init();
  moteur_treuil.init(moteur_pin);
  moteur_treuil.marche(0,0);
}

void loop()
{
  float r,t;
  int i;

  while(1)
  {
    r = potar.get_tour();
    t = treuil.get_tour();
    moteur_treuil.marche(0,r*20);
    if (!digitalRead(button_pin))
    {
      while(!digitalRead(button_pin));
      potar.raz();
      treuil.raz();
    }
    if (i > 150)
    {
      Serial.print("\nr:");
      Serial.print(r);
      Serial.print(" t:");
      Serial.print(t);
      Serial.print(" boutton : ");
      Serial.print(digitalRead(button_pin));
      i = 0;
    }
    i++;
  }
}


