#include "moteur.h"
#include "compteur.h"
//#include <arduino.h>
#include "eeprom.h"

#define tempo_rebond  500

class treuil
{
public:
                                            // constructeur avec pin bouton et PPM, et adresse de sauvegarde en eeprom
  treuil(char button, char adr_treuil_max, char adr_treuil_min,
         char adr_joy_max, char adr_joy_min, char adr_joy_neutre);
  void calibration(void);                   // fonction de calibration manche et treuil
  void init(char adr_enc1, char adr_eeprom_nb_tour_pot, char adr_enc2, char adr_eeprom_nb_tour_treuil, char moteur,char moteur_pwm1, char moteur_pwm2);  // init du treuil
  void marche(void);                        // contrôle le moteur en fonction du potar suivant le mode choisi
  moteur moteur_treuil;                     // instanciation moteur
  compteur c_potar;                         // instanciation potar type compteur
  compteur c_treuil;                        // instanciation treuil type compteur
  char mode;                                // mode vitesse (0) ou position (1)
  float treuil_max, treuil_min, pot_max, pot_min, pot_neutre;
private:
  char button_pin, adr_ee_treuil_max, adr_ee_treuil_min,
          adr_ee_joy_max, adr_ee_joy_min, adr_ee_joy_neutre;
  float last_speed;                         // vitesse treuil en mode position
  float last_pos;                           // derniere position demandée
  unsigned long last_time;                  // tempo pour rampe d'accélération
};
