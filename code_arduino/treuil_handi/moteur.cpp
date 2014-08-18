#include "moteur.h"

Servo myservo;

void moteur::marche (signed char speed)
{
  // gestion d'un signal PPM
  signed int commande;
  commande = speed * 90;                // commande + ou - 90° de servo
  commande = commande / 100;
  commande += 91;                       // offset pour qu'une commande 0 soit le point milieu
  myservo.write(commande);              // envoi de la commande au servo
  
  // gestion 2 signaux PWM pour pont en H
  float calcul;
  char value1, value2;
  if (speed >=0)
  {
    value2 = 0;
    calcul = speed;
    calcul = calcul *2.55;
    value1 = calcul;
  }
  else
  {
    value1 = 0;
    calcul = -speed;
    calcul = calcul *2.55;
    value2 = calcul;
  }
  analogWrite(p_pwm1, value1);
  analogWrite(p_pwm2, value2);
}

void moteur::init (char pin_servo, char pin_pwm1, char pin_pwm2)
{
  myservo.attach(pin_servo);
  p_pwm1 = pin_pwm1;
  p_pwm2 = pin_pwm2;
  pinMode(p_pwm1, OUTPUT);
  pinMode(p_pwm2, OUTPUT);
}
