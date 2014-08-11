//Pour arduino 1.05


// Variation avec 2 boutons comme commande
// commencée le 9 août 2014
// limitation à maximum un tour pour la commande en séparant les routines commande des routines contrôle

// Trois boutons poussoirs simulent 2 capteurs à effet hall devant lesquels un aimant se déplace successivement


#include <Wire.h>
#include <EEPROM.h>
#include <Servo.h> 
#include "fonctions_treuil.h"

#define button_pin  12                             // broche du bouton
#define moteur_pin  11                             // broche du PPM
#define led_pin     13                             // broche led
#define button_av_pin   4                          // poussoir avant
#define button_ar_pin   7                          // poussoir arrière
#define adr_enc2  65       
#define adr_eeprom_nb_tour_treuil  4               // adresse en eeprom nb de tour du treuil
#define adr_eeprom_treuil_max  8                   // adresse en eeprom position treuil maxi
#define adr_eeprom_treuil_min  12                  // adresse en eeprom position treuil mini

#define debug  1                                   //active debug sur rs232

treuil treuil_1(button_pin, moteur_pin, adr_eeprom_treuil_max, adr_eeprom_treuil_min,button_av_pin, button_ar_pin);

void setup()
{
  Serial.begin(9600);                              // start serial for output
  
  delay(3000);                                     // pour attendre que l'on ouvre l'afficheur série
  Serial.println("Treuil-Handi-2 boutons");
  
  treuil_1.init(adr_enc2, adr_eeprom_nb_tour_treuil);
  pinMode(led_pin, OUTPUT);
  
}

void loop()
{
  float t;
  int tempo_calib, i=0;
  
  tempo_calib = 0;
  while(tempo_calib < 500)                                  // phase calibration
  {
    if (!digitalRead(button_pin))
    {
      while(!digitalRead(button_pin));                      // attente relâchement bouton
      delay(tempo_rebond);                                  // anti-rebond
      Serial.println("calibration");
      treuil_1.calibration();
      tempo_calib = 500;                                    // on sort de la boucle si calibration
    }
    delay(10);
    tempo_calib++;
    if (tempo_calib % 20 == 1)
    {    digitalWrite(led_pin, !digitalRead(led_pin));}     // clignotement de la led pendant toute la durée
  }                                                         // où la calibration peut être déclenchée
  
  digitalWrite(led_pin, HIGH);                              // led allumée
  
   while(1) //marche normale
  {
    treuil_1.marche();
    if (i > 250 && debug)
    {
      
      t = treuil_1.c_treuil.get_tour();
      Serial.print(" t:");
      Serial.print(t);
      //Serial.print(" bt :");
      //Serial.print(digitalRead(button_pin));       
      Serial.print("  t_mini : ");
      Serial.print(treuil_1.treuil_min);
      Serial.print("    t_maxi : ");
      Serial.println(treuil_1.treuil_max);
      i = 0;
    }
    i++;
  }
}

