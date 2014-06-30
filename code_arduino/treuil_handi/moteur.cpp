#include "moteur.h"
#include <Servo.h> 

Servo myservo;

void moteur::marche (char sens, char speed)
{
  int commande;
  commande = speed * 90;                //commande + ou - 90° de servo
  commande = commande / 100;
  commande = commande * (-1 + 2 * sens);
  commande += 90;                      //offset pour qu'une commande 0 soit le point milieu
  myservo.write(commande);             //envoie la commande au servo
}

void moteur::init (char pin)
{
  myservo.attach(pin);
}
