#include "moteur.h" 

Servo myservo;

void moteur::marche (signed char speed)
{
  signed int commande;
  commande = speed * 90;                // commande + ou - 90° de servo
  commande = commande / 100;
  commande += 95;                       // offset pour qu'une commande 0 soit le point milieu
  myservo.write(commande);              // envoi de la commande au servo
}

void moteur::init (char pin)
{
  myservo.attach(pin);
}
