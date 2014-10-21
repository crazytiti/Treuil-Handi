#include "moteur.h"

#define force_frein 255                // force du frein à l'arret de 0 à 255
Servo myservo;

void moteur::marche (signed char speed)
{
  // gestion d'un signal PPM
  signed int commande;
  commande = speed * 90;                // commande + ou - 90° de servo
  commande = commande / 100;
  commande += 91;                       // offset pour qu'une commande 0 soit le point milieu
  myservo.write(commande);              // envoi de la commande au servo
  
  // gestion d'un signal PWM
  float calcul;
  char pwm_value;
  if (speed >0)                         // marche avant
  {
    calcul = speed;                     // conversion de % à 0-255
    calcul = calcul *2.55;
    pwm_value = calcul;
    digitalWrite(p_left, HIGH);         // mosfet gauche sur Vcc et mosfet droit GND
    digitalWrite(p_right, LOW);
  }
  else if (speed <0)
  {
    calcul = -speed;
    calcul = calcul *2.55;
    pwm_value = calcul;
    digitalWrite(p_left, LOW);          // mosfet gauche sur GND et mosfet droit Vcc
    digitalWrite(p_right, HIGH);
  }
  else if (speed == 0)    //frein à l'arret avec mosfet droit et gauche sur GND
  {
    pwm_value = force_frein;            // application de la force du frein
    digitalWrite(p_left, LOW);
    digitalWrite(p_right, LOW);
  }
  analogWrite(p_pwm, pwm_value);        // active le PWM à la proportion voulue
}

void moteur::beep(signed char frequence)
{
  int i;
  for(i=0;i<100;i++)
  {
  digitalWrite(p_left, HIGH);         // mosfet gauche sur Vcc et mosfet droit GND
  digitalWrite(p_right, LOW);
  analogWrite(p_pwm, Beep_pwm);        // active le PWM à la proportion voulue
  delay(frequence);
  digitalWrite(p_left, LOW);          // mosfet gauche sur GND et mosfet droit Vcc
  digitalWrite(p_right, HIGH);
  analogWrite(p_pwm, Beep_pwm);        // active le PWM à la proportion voulue
  delay(frequence);
  }
  analogWrite(p_pwm, 0);              // ARRET
}

void moteur::init (char pin_servo, char pin_pwm, char pin_left, char pin_right)
{
  myservo.attach(pin_servo);
  p_pwm = pin_pwm;
  p_left = pin_left;
  p_right = pin_right;
  pinMode(p_pwm, OUTPUT);
  pinMode(p_left, OUTPUT);
  pinMode(p_right, OUTPUT);
}
