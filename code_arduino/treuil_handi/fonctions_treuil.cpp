#include "fonctions_treuil.h"

#define zone_neutre  5    //marge du neutre du potar en %
#define zone_max  5       //marge à partir de laquelle on considere +- 100%

treuil::treuil(char button, char moteur, char adr_treuil_max, char adr_treuil_min,
                char adr_joy_max, char adr_joy_min, char adr_joy_neutre)
{
  button_pin = button;          //pin boutton
  moteur_pin = moteur;          //pin PPM
  adr_ee_treuil_max = adr_treuil_max;
  adr_ee_treuil_min = adr_treuil_min;
  adr_ee_joy_max = adr_joy_max;
  adr_ee_joy_min = adr_joy_min;
  adr_ee_joy_neutre = adr_joy_neutre;
  mode = 0;                    //mode proportionel par défaut
}
void treuil::calibration (void)
{
  // min et max du treuil
  c_treuil.raz();
  moteur_treuil.marche(15);    //moteur avant lente
  while (digitalRead(button_pin))
  {
    treuil_max = c_treuil.get_tour();
  }
  delay(tempo_rebond);                    //anti-rebond
  //sauvegarde position
  treuil_max = c_treuil.get_tour();
  ee_ecrit(adr_ee_treuil_max, (char*)&treuil_max, 4);
  
  moteur_treuil.marche(-15);    //moteur arriere lente
  while (digitalRead(button_pin))
  {
    treuil_min = c_treuil.get_tour();
  }
  moteur_treuil.marche(0);      //arret moteur
  delay(tempo_rebond);                    //anti-rebond
  //sauvegarde position
  treuil_min = c_treuil.get_tour();
  ee_ecrit(adr_ee_treuil_min, (char*)&treuil_min, 4);
  
  //min et max joystick
  c_potar.raz();
  pot_max = -10;
  pot_min = 10;
  pot_neutre = 0;
  float act_pos;
  while (digitalRead(button_pin))
  {
    act_pos = c_potar.get_tour();
    act_pos += c_potar.get_tour();
    act_pos += c_potar.get_tour();
    act_pos += c_potar.get_tour();
    act_pos = act_pos /4;
    if (act_pos > pot_max){
      pot_max = act_pos;
    }
    if (act_pos < pot_min){
      pot_min = act_pos;
    }
    //Serial.print("\n act_pos:");
    //Serial.print(act_pos);
  }
  pot_neutre = c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre = pot_neutre / 4;
  //sauvegarde les 3 positions en eeprom
  ee_ecrit(adr_ee_joy_max, (char*)&pot_max, 4);
  ee_ecrit(adr_ee_joy_min, (char*)&pot_min, 4);
  ee_ecrit(adr_ee_joy_neutre, (char*)&pot_neutre, 4);
  delay(tempo_rebond);                    //anti-rebond
}

void treuil::init(char adr_enc1, char adr_eeprom_nb_tour_pot, char adr_enc2, char adr_eeprom_nb_tour_treuil)
{
  c_potar.set_compteur(adr_enc1, adr_eeprom_nb_tour_pot);        //recupere la position du potar en eeprom
  c_treuil.set_compteur(adr_enc2, adr_eeprom_nb_tour_treuil);    //recupere la position du treuil en eeprom
  pinMode(button_pin, INPUT_PULLUP);                             //pull up du boutton
  c_potar.init();                                                //init des 2 compteurs potar et treuil
  c_treuil.init();
  moteur_treuil.init(moteur_pin);                                //init du moteur
  moteur_treuil.marche(0);                                     //mise à l'arret du moteur
  etat = 0;                                                      //machine a etat
  ee_lit(adr_ee_treuil_max, (char*)&treuil_max, 4);              //récupere en eeprom toutes les valeures
  ee_lit(adr_ee_treuil_min, (char*)&treuil_min, 4);
  ee_lit(adr_ee_joy_max, (char*)&pot_max, 4);
  ee_lit(adr_ee_joy_min, (char*)&pot_min, 4);
  ee_lit(adr_ee_joy_neutre, (char*)&pot_neutre, 4);
}

void treuil::marche()
{
  float pot_value;
  switch(mode){
    case 0:      //mode proportionel
      pot_value = c_potar.get_tour()*200 / (pot_max - pot_min);    //calcule la valeure de déplacement en + - 100%
      pot_value = pot_value * (100 / (100- zone_max));             //expansion de la dynamique du potar en fonction de la marge par rapport au maxi
      if (pot_value > 100)      //bornage
      {pot_value = 100;}
      if (pot_value < -100)
      {pot_value = -100;}
      //Serial.print(" pot_v : "); //debug
      //Serial.print(pot_value);      //debug
      if (pot_value > zone_neutre)  //marche avant
      {
        if (c_treuil.get_tour() < treuil_max)
        {
          moteur_treuil.marche(pot_value);
        }
        else
        {
          moteur_treuil.marche(0);
        }
      }
      else if (pot_value < - zone_neutre)  //marche arriere
      {
        if (c_treuil.get_tour() > treuil_min)
        {
          moteur_treuil.marche(pot_value);
        }
        else
        {
          moteur_treuil.marche(0);
        }
      }    
      else  //arret
      {
        moteur_treuil.marche(0);
      }
      break;
    case 1:      //mode impulsionel
      
      break;
  }
}
