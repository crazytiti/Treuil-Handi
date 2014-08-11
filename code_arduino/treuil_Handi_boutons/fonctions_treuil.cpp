#include "fonctions_treuil.h"

#define  zone_max  5                            // marge à partir de laquelle on considère +- 100%
#define  ramp_speed  8000                       // durée (en ms) pour atteindre 100% de vitesse en mode impulsionnel
#define  min_speed  9                           // vitesse de démarrage du mode impulsionnel



treuil::treuil(char button, char moteur, char adr_treuil_max, char adr_treuil_min, char button_av, char button_ar)

{
  button_pin = button;                          // pin bouton
  moteur_pin = moteur;                          // pin PPM
  button_av_pin = button_av;
  button_ar_pin = button_ar;
  adr_ee_treuil_max = adr_treuil_max;
  adr_ee_treuil_min = adr_treuil_min;
  
}






void treuil::init(char adr_enc2, char adr_eeprom_nb_tour_treuil)
{
  //Serial.println("treuil.init");
  c_treuil.set_compteur(adr_enc2, adr_eeprom_nb_tour_treuil);    // récupère la position du treuil en eeprom
  pinMode(button_pin, INPUT_PULLUP);                             // pull up du boutton
  pinMode(button_av_pin, INPUT_PULLUP);                          // pull up des boutons du manche 
  pinMode(button_ar_pin, INPUT_PULLUP);   
  c_treuil.init();
  moteur_treuil.init(moteur_pin);                                // init du moteur
  moteur_treuil.marche(0);                                       // mise à l'arrêt du moteur
  Serial.println("Servo immobile");
  Serial.println("");
  delay(1000);
  last_speed = 0;                                                // init à 0 en mode impulsionnel
  last_time = millis();                                          // mémorisation de l'heure
  
  ee_lit(adr_ee_treuil_max, (char*)&treuil_max, 4);              // récupère en eeprom toutes les valeurs
  ee_lit(adr_ee_treuil_min, (char*)&treuil_min, 4);                          
}



void treuil::calibration (void)
{
                                                   // min et max du treuil
  c_treuil.raz();
  moteur_treuil.marche(-7);                         // moteur avant lent
  Serial.println("En avant lent vers fin de course");
  Serial.println(" Appuyer sur le bouton quand on y est. ");
  while (digitalRead(button_pin))                  // attend tant que le bouton n'est pas appuyé
  {                                                // le treuil tourne pendant ce temps
    treuil_max = c_treuil.get_tour();              // indispensable pour enregistrer le nb de tours
  }
  moteur_treuil.marche(0);                         // arrêt moteur
  Serial.println("Appui sur le bouton : OK");
                
  while (!digitalRead(button_pin));                 // attend le relâchement du bouton
  delay(tempo_rebond);                             // anti-rebond
                                                   // sauvegarde position
  Serial.print("treuil_max = ");
  Serial.println(treuil_max);
  Serial.println("");
  ee_ecrit(adr_ee_treuil_max, (char*)&treuil_max, 4);
  
  moteur_treuil.marche(9);                        // moteur arrière lent
  while (digitalRead(button_pin))                  // attend tant que le bouton n'est pas appuyé
  {
    treuil_min = c_treuil.get_tour();              // utile pour connaître le nb de tours
  }
  moteur_treuil.marche(0);                         // arrêt moteur
  
  
  while (!digitalRead(button_pin));                // attend tant que le bouton est appuyé
  delay(tempo_rebond);                             // anti-rebond
                                                   // sauvegarde position
  treuil_min = c_treuil.get_tour();  
  Serial.print("treuil_min = ");
  Serial.println(treuil_min);
  Serial.println("");  
  ee_ecrit(adr_ee_treuil_min, (char*)&treuil_min, 4);
  
}




void treuil::marche()
{
  float manche_value=0;
  last_time = millis();
  if (!digitalRead(button_av_pin))
      {
      manche_value = -100;
      }
  if (!digitalRead(button_ar_pin))
      {
      manche_value = +100;
      }
  
  while ((millis() - last_time) < 10)  ;                         // on sort que si 10ms se sont écoulées
  if (last_speed > 0)                                            // suivant état précédent du treuil : sens avant
    {
    if (manche_value < 0)
      {
      last_speed = last_speed + 100.00 / (ramp_speed / 10.00);   // accélération suivant rampe
      if (last_speed > 100)
        {
        last_speed = 100;
        }
      }
    else if (manche_value == 0)
      {
      last_speed = 0;                                         // plus aucun bouton appuyé donc arrêt
      } 
    }
  else if (last_speed < 0)                                    // suivant état précédent du treuil : sens arrière
    {
    if (manche_value > 0)
      {
      last_speed = last_speed - 100.00 / (ramp_speed / 10.00); // accélération suivant rampe
      if (last_speed < -100)
        {
        last_speed = -100;
        }
      }
    else if (manche_value ==0)
      {
      last_speed = 0;                                          // plus aucun bouton appuyé donc arrêt
      }
    }
  else                                                         // suivant état précédent du treuil : à l'arrêt
    {
    if (manche_value > 0 and last_speed == 0)
      {
      last_speed = min_speed;                                  // mise en marche avant lent
      }
    else if (manche_value <0 and last_speed == 0)
      { 
      last_speed = -min_speed;                                 // mise en marche arrière lent
      }
    }
                                                                // -----------gestion des butées ------
  if (last_speed > 0)
    {
    if (c_treuil.get_tour() <= treuil_min)                    // max atteint => arrêt
      {
      last_speed = 0;
      }
    }
  else if (last_speed < 0)
    {
    if (c_treuil.get_tour() >= treuil_max)                   // min atteint => arrêt
      {
      last_speed = 0;
      }
    }
  moteur_treuil.marche(last_speed);                          // envoi de la commande au moteur
    
}




