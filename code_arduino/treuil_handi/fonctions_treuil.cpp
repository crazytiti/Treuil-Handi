#include "fonctions_treuil.h"

#define  zone_neutre  5                         // marge du neutre du potar en %
#define  zone_neutre_impu  25                   // marge du neutre du potar en % en mode impulsionnel
#define  zone_max  5                            // marge à partir de laquelle on considère +- 100%
#define  ramp_speed  3000                       // durée (en ms) pour atteindre 100% de vitesse en mode impulsionnel
#define  min_speed  5                           // vitesse de démarrage du mode impulsionnel



treuil::treuil(char button, char moteur, char adr_treuil_max, char adr_treuil_min,
char adr_joy_max, char adr_joy_min, char adr_joy_neutre)
{
  button_pin = button;                          // pin boutton
  moteur_pin = moteur;                          // pin PPM
  adr_ee_treuil_max = adr_treuil_max;
  adr_ee_treuil_min = adr_treuil_min;
  adr_ee_joy_max = adr_joy_max;
  adr_ee_joy_min = adr_joy_min;
  adr_ee_joy_neutre = adr_joy_neutre;
  mode = 0;                                     // mode proportionnel par défaut
}





void treuil::calibration (void)
{
  // min et max du treuil
  c_treuil.raz();
  moteur_treuil.marche(5);                         // moteur avant lent
  Serial.println("En avant lent jusqu'à fin de course");
  Serial.println(" appui sur le bouton quand on y est. ");
  while (digitalRead(button_pin))                  // attend tant que le bouton n'est pas appuyé
  {                                                // le treuil tourne pendant ce temps
    treuil_max = c_treuil.get_tour();              // indispensable pour enregistrer le nb de tours
  }
  moteur_treuil.marche(0);                         // arrêt moteur
  Serial.println("Appui sur le bouton");
                
  while (!digitalRead(button_pin));                // attend le relâchement du bouton
  delay(tempo_rebond);                             //anti-rebond
                                                   //sauvegarde position
  //treuil_max = c_treuil.get_tour();                          
  Serial.print("treuil_max = ");
  Serial.println(treuil_max);
  Serial.println("");
  ee_ecrit(adr_ee_treuil_max, (char*)&treuil_max, 4);
  
  moteur_treuil.marche(-5);                        // moteur arrière lent
  while (digitalRead(button_pin))                  // attend tant que le bouton n'est pas appuyé
  {
    treuil_min = c_treuil.get_tour();              // utile pour connaître le nb de tours
  }
  moteur_treuil.marche(0);                         // arrêt moteur
  while (!digitalRead(button_pin));                // attend tant que le bouton est appuyé
  delay(tempo_rebond);                             //anti-rebond
                                                   //sauvegarde position
  treuil_min = c_treuil.get_tour();  
  Serial.print("treuil_min = ");
  Serial.println(treuil_min);
  Serial.println("");  
  ee_ecrit(adr_ee_treuil_min, (char*)&treuil_min, 4);

                                                    //min et max joystick
  Serial.println("Calibration du joystick");
  Serial.println("");
  c_potar.raz();
  pot_max = -10;
  pot_min = 10;
  pot_neutre = 0;
  float act_pos;
  Serial.println("Faire bouger le manche du joystick plusieurs fois du minimum au maximum");
  Serial.println("");
  Serial.println("Puis le mettre au neutre avant d'appuyer sur le bouton");
  Serial.println("");
  while (digitalRead(button_pin))                 // tant qu'on appuie pas sur le bouton
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
                                            // on a les valeurs max et min et on sort de la boucle par appui
                                            // sur le bouton. Au préalable bien ramener le joystick au neutre.
  pot_neutre = c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre += c_potar.get_tour();
  pot_neutre = pot_neutre / 4;              // moyenne 
  //sauvegarde les 3 positions en eeprom
  ee_ecrit(adr_ee_joy_max, (char*)&pot_max, 4);
  ee_ecrit(adr_ee_joy_min, (char*)&pot_min, 4);
  ee_ecrit(adr_ee_joy_neutre, (char*)&pot_neutre, 4);
  delay(tempo_rebond);                      //anti-rebond
}



void treuil::init(char adr_enc1, char adr_eeprom_nb_tour_pot, char adr_enc2, char adr_eeprom_nb_tour_treuil)
{
  Serial.println("treuil.init");
  c_potar.set_compteur(adr_enc1, adr_eeprom_nb_tour_pot);        // récupère la position du potar en eeprom
  c_treuil.set_compteur(adr_enc2, adr_eeprom_nb_tour_treuil);    // récupère la position du treuil en eeprom
  pinMode(button_pin, INPUT_PULLUP);                             // pull up du boutton
  c_potar.init();                                                // init des 2 compteurs potar et treuil
  c_treuil.init();
  moteur_treuil.init(moteur_pin);                                // init du moteur
  moteur_treuil.marche(0);                                       // mise à l'arrêt du moteur
  Serial.println("servo à l'arrêt");
  Serial.println("");
  
             // Sous-programme permettant d'adapter le neutre du servo ???
   
  delay(1000);
  last_speed = 0;                                                // init à 0 en mode impulsionnel
  last_time = millis();                                          // mémorisation de l'heure
  a_retour = 0;                                                  // init anti retour
  ee_lit(adr_ee_treuil_max, (char*)&treuil_max, 4);              // récupère en eeprom toutes les valeurs
  ee_lit(adr_ee_treuil_min, (char*)&treuil_min, 4);
  ee_lit(adr_ee_joy_max, (char*)&pot_max, 4);
  ee_lit(adr_ee_joy_min, (char*)&pot_min, 4);
  ee_lit(adr_ee_joy_neutre, (char*)&pot_neutre, 4);
}



void treuil::marche()
{
  float pot_value;                                  // valeur potentiomètre
  pot_value = c_potar.get_tour();
                                                    // calcul la valeur de déplacement en + - 100%
  if (pot_value >= pot_neutre)                      // déplacement positif
  {
    pot_value = (pot_value - pot_neutre) * 100 / (pot_max - pot_neutre);
  }
  else                                              // déplacement négatif
  {
    pot_value = (pot_value - pot_neutre) * 100 / (pot_neutre - pot_min);
  }  
  pot_value = pot_value * (100 / (100- zone_max));  // expansion de la dynamique du potar en fonction de la marge par rapport au maxi
  if (pot_value > 100)                              // bornage
  {
    pot_value = 100;
  }
  if (pot_value < -100)
  {
    pot_value = -100;
  }
  //Serial.print(" pot_v : ");                      // debug
  //Serial.print(pot_value);                        // debug
  switch(mode){
  case 0:                                           // mode proportionnel
    if (pot_value > zone_neutre)                    // marche avant
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
    else if (pot_value < - zone_neutre)             // marche arrière
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
  case 1:                                         // mode impulsionnel, fréquence de rafraichissement 10ms (100hz)
    if ((millis() - last_time) < 10)              // on sort si 10ms ne se sont pas écoulées
    {
      break;
    }
    last_time = millis();                         // mémorisation de l'heure
    if (last_speed > 0)                           // suivant état précédent du treuil : sens avant
    {
      if (pot_value > zone_neutre_impu)
      {
        last_speed = last_speed + 100.00 / (ramp_speed / 10.00);   // accélération suivant rampe
        if (last_speed > 100)
        {
          last_speed = 100;
        }
      }
      else if (pot_value < - zone_neutre_impu)
      {
        last_speed = 0;                          // arrêt suite à manoeuvre inverse du pot
        a_retour = 1;                            // activation de l'anti-retour
      }
    }
    else if (last_speed < 0)                     // suivant état précédent du treuil : sens arrière
    {
      if (pot_value < - zone_neutre_impu)
      {
        last_speed = last_speed - 100.00 / (ramp_speed / 10.00);   // accélération suivant rampe
        if (last_speed < -100)
        {
          last_speed = -100;
        }
      }
      else if (pot_value > zone_neutre_impu)
      {
        last_speed = 0;                          // arrêt suite à manoeuvre inverse du pot
        a_retour = 1;                            // activation de l'anti-retour
      }
    }
    else                                         // suivant état précédent du treuil : à l'arrêt
    {
      if (pot_value > zone_neutre_impu && !a_retour)
      {
        last_speed = min_speed;                  // mise en marche avant lent
      }
      else if (pot_value < - zone_neutre_impu && !a_retour)
      { 
        last_speed = -min_speed;                 // mise en marche arrière lent
      }
      else if (pot_value > - zone_neutre_impu && pot_value < zone_neutre_impu)
      {
                                                 // potar au neutre on désactive l'anti retour        
        a_retour = 0;
      }
    }
                                                 // -----------gestion des butées ------
    if (last_speed > 0)
    {
      if (c_treuil.get_tour() >= treuil_max)     // max atteint => arrêt
      {
        last_speed = 0;
      }
    }
    else if (last_speed < 0)
    {
      if (c_treuil.get_tour() <= treuil_min)      // min atteint => arrêt
      {
        last_speed = 0;
      }
    }
    moteur_treuil.marche(last_speed);             //envoi de la commande au moteur
    break;
  }
}




