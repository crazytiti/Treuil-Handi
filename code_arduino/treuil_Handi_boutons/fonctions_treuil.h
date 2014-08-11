#include "moteur.h"
#include "compteur.h"
#include <arduino.h>
#include "eeprom.h"

#define tempo_rebond  500

class treuil
{
public:
                                            // constructeur avec pin bouton et PPM, et adresse de sauvegarde en eeprom
  treuil(char button, char moteur, char adr_treuil_max, char adr_treuil_min, char button_av, char button_ar);
         
  void init(char adr_enc2, char adr_eeprom_nb_tour_treuil);  // init du treuil
        
  void calibration(void);                   // fonction de calibration manche et treuil
  void marche(void);                        // contrôle le moteur en fonction du potar suivant le mode choisi
  
  moteur moteur_treuil;                     // instanciation moteur
  compteur c_treuil;                        // instanciation treuil type compteur
  float treuil_max, treuil_min, pot_max, pot_min, pot_neutre;
private:
  char button_pin, moteur_pin, adr_ee_treuil_max, adr_ee_treuil_min,button_av_pin, button_ar_pin;
  float last_speed;                         // vitesse treuil en mode impulsionnel
  unsigned long last_time;                  // tempo pour rampe d'accélération
  char a_retour;                            // anti retour pour arrêt lors d'une manoeuvre inverse en mode impulsionnel
};
