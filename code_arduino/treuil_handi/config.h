/*      ___________
          BROCHES
        -----------
*/

#define boutton_pin  12                           // broche du bouton
#define moteur_pin  11                            // broche du PPM
#define moteur_pwm_pin 6                          // broche PWM
#define moteur_left_pin 7                         // broche mosfet "gauche"
#define moteur_right_pin 8                        // broche mosfet "droit"
#define led_pin     13                            // broche led

/*      ___________
          Adresses
        -----------
*/
#define adr_enc1  64                              // adresse encodeur potar
#define adr_enc2  65                              // adresse encodeur treuil

/*      _______________________
        paramètres mécanniques
        -----------------------
*/
#define  calib_speed  10                          // vitesse "lente" de calibration treuil
#define  zone_neutre  5.0                         // marge du neutre du potar en % (le .0 force le type float)
#define  zone_neutre_pos  3.0                     // marge du neutre en % en mode position (deplacement mini)
#define  zone_max  5.0                            // marge à partir de laquelle on considère +- 100%
#define  ramp_speed  3000                         // durée (en ms) pour atteindre 100% de vitesse en mode position
#define  min_speed  5                             // vitesse de démarrage du mode position
#define  jeu_mini  3.0                            // plage de jeu mécannique avant que le treuil ne compense le mouvement en mode position

/*      ________________
        Debug par rs232
        ----------------
*/
#define debug  1                                  //active debug sur rs232
