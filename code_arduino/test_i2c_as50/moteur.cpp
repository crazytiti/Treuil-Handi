#include "moteur.h"
Servo myservo;

void moteur::marche (char sens, char speed)
{
  int commande;
  commande = speed * 90;                //commande + ou - 90° de servo
  commande = commande / 100;
  commande = commande * (-1 + 2 * sens);
  commande += 90;
  myservo.write(commande);
}

void moteur::init (char pin)
{
  myservo.attach(pin);
}
