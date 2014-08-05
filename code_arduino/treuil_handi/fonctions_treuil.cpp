#include "fonctions_treuil.h"

#define  zone_neutre  5    //marge du neutre du potar en %
#define  zone_neutre_impu  25    //marge du neutre du potar en % en mode impulsionel
#define  zone_max  5       //marge à partir de laquelle on considere +- 100%
#define  ramp_speed  3000    //durée (en ms) pour atteindre 100% de vitesse en mode impulsionel
#define  min_speed  5      //vitesse de démarrage du mode impulsionnele

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
  moteur_treuil.marche(0);      //arret moteur
  while (!digitalRead(button_pin));
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
  while (!digitalRead(button_pin));
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
  last_speed = 0;                                              //init à 0 en mode impulsionel
  last_time = millis();                                        //mémorisation de l'heure
  a_retour = 0;                                                //init anti retour
  ee_lit(adr_ee_treuil_max, (char*)&treuil_max, 4);              //récupere en eeprom toutes les valeures
  ee_lit(adr_ee_treuil_min, (char*)&treuil_min, 4);
  ee_lit(adr_ee_joy_max, (char*)&pot_max, 4);
  ee_lit(adr_ee_joy_min, (char*)&pot_min, 4);
  ee_lit(adr_ee_joy_neutre, (char*)&pot_neutre, 4);
}

void treuil::marche()
{
  float pot_value;    //valeure potentiometre
  pot_value = c_potar.get_tour();
  //calcule la valeure de déplacement en + - 100%
  if (pot_value >= pot_neutre)    //deplacement positif
  {
    pot_value = (pot_value - pot_neutre) * 100 / (pot_max - pot_neutre);
  }
  else                            //deplacement negatif
  {
    pot_value = (pot_value - pot_neutre) * 100 / (pot_neutre - pot_min);
  }  
  pot_value = pot_value * (100 / (100- zone_max));             //expansion de la dynamique du potar en fonction de la marge par rapport au maxi
  if (pot_value > 100)      //bornage
  {
    pot_value = 100;
  }
  if (pot_value < -100)
  {
    pot_value = -100;
  }
  //Serial.print(" pot_v : "); //debug
  //Serial.print(pot_value);      //debug
  switch(mode){
  case 0:      //mode proportionel
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
  case 1:      //mode impulsionel, frequence de rafraichissement 10ms (100hz)
    if ((millis() - last_time) < 10)      //on sort si 10ms ne se sont pas ecoulees
    {
      break;
    }
    last_time = millis();      //mémorisation de l'heure
    if (last_speed > 0)      //suivant état précédent du treuil : sens avant
    {
      if (pot_value > zone_neutre_impu)
      {
        last_speed = last_speed + 100.00 / (ramp_speed / 10.00);      //acceleration suivant rampe
        if (last_speed > 100)
        {
          last_speed = 100;
        }
      }
      else if (pot_value < - zone_neutre_impu)
      {
        last_speed = 0; //arret suite a maneuvre inverse du pot
        a_retour = 1;  //activation de l'anti-retour
      }
    }
    else if (last_speed < 0)   //suivant état précédent du treuil : sens arriere
    {
      if (pot_value < - zone_neutre_impu)
      {
        last_speed = last_speed - 100.00 / (ramp_speed / 10.00);      //acceleration suivant rampe
        if (last_speed < -100)
        {
          last_speed = -100;
        }
      }
      else if (pot_value > zone_neutre_impu)
      {
        last_speed = 0; //arret suite a maneuvre inverse du pot
        a_retour = 1;  //activation de l'anti-retour
      }
    }
    else             //suivant état précédent du treuil : a l'arret
    {
      if (pot_value > zone_neutre_impu && !a_retour)
      {
        last_speed = min_speed;        //mise en marche avant lente
      }
      else if (pot_value < - zone_neutre_impu && !a_retour)
      { 
        last_speed = -min_speed;      //mise en marche arriere lente
      }
      else if (pot_value > - zone_neutre_impu && pot_value < zone_neutre_impu)
      {
        //potar au neutre on desactive l'anti retour        
        a_retour = 0;
      }
    }
    // -----------gestion des butes ------
    if (last_speed > 0)
    {
      if (c_treuil.get_tour() >= treuil_max)      //max atteint => arret
      {
        last_speed = 0;
      }
    }
    else if (last_speed < 0)
    {
      if (c_treuil.get_tour() <= treuil_min)      //min atteint => arret
      {
        last_speed = 0;
      }
    }
    moteur_treuil.marche(last_speed);  //envoie de la commande au moteur
    break;
  }
}




