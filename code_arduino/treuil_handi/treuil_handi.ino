//Pour arduino 1.05

#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h> 
#include "fonctions_treuil.h"

#define button_pin  12              //broche du bouton
#define moteur_pin  13              //broche du PPM
#define adr_enc1  64                //adresse encodeur potar
#define adr_enc2  65                //adresse encodeur treuil
#define adr_eeprom_nb_tour_pot  0     //adresse en eeprom nb de tour du pot
#define adr_eeprom_nb_tour_treuil  4  //adresse en eeprom nb de tour du treuil
#define adr_eeprom_treuil_max  8      //adresse en eeprom position treuil maxi
#define adr_eeprom_treuil_min  12     //adresse en eeprom position treuil mini
#define adr_eeprom_pot_max  16        //adresse en eeprom position potar maxi
#define adr_eeprom_pot_min  20        //adresse en eeprom position potar mini
#define adr_eeprom_pot_neutre  24     //adresse en eeprom position potar neutre

treuil treuil_1(button_pin, moteur_pin, adr_eeprom_treuil_max, adr_eeprom_treuil_min,
                adr_eeprom_pot_max, adr_eeprom_pot_min, adr_eeprom_pot_neutre);

void setup()
{
  Serial.begin(9600);  // start serial for output
  treuil_1.init(adr_enc1, adr_eeprom_nb_tour_pot, adr_enc2, adr_eeprom_nb_tour_treuil);
}

void loop()
{
  float r,t;
  int tempo_calib, i=0;
  
  tempo_calib = 0;
  while(tempo_calib < 500)   //phase calibration
  {
    if (!digitalRead(button_pin))
    {
      while(!digitalRead(button_pin));    //attente relachement boutton
      delay(tempo_rebond);                    //anti-rebond
      treuil_1.calibration();
      tempo_calib = 500;    //on sort de la boucle si calibration
    }
    delay(10);
    tempo_calib++;
  }

  while(1)    //marche normale
  {
    r = treuil_1.c_potar.get_tour();
    t = treuil_1.c_treuil.get_tour();
    //treuil_1.moteur_treuil.marche(r*20);
    //treuil_1.marche();
    if (!digitalRead(button_pin))
    {
      
      treuil_1.c_potar.raz();
      treuil_1.c_treuil.raz();
    }
    if (i > 250)
    {
      Serial.print("\nr:");
      Serial.print(r);
      Serial.print(" t:");
      Serial.print(t);
      Serial.print(" bt:");
      Serial.print(digitalRead(button_pin));
      Serial.print(" min:");
      Serial.print(treuil_1.pot_min);
      Serial.print(" max:");
      Serial.print(treuil_1.pot_max);
      Serial.print(" nt:");
      Serial.print(treuil_1.pot_neutre);
      Serial.print(" t_mn:");
      Serial.print(treuil_1.treuil_min);
      Serial.print(" t_mx:");
      Serial.print(treuil_1.treuil_max);
      treuil_1.marche();
      i = 0;
    }
    i++;
  }
}

