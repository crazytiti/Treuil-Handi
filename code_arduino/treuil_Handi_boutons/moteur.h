#include <Servo.h>

class moteur
{
public:
  void marche (signed char speed);                   //commande le moteur de -100% à +100%
  void init(char pin);
};
