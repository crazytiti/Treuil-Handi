#include <Servo.h>
#include "config.h"
#include <arduino.h>

class moteur
{
public:
  void marche (signed char speed);                   // commande le moteur de -100% à +100%
  void init(char pin_servo, char pin_pwm, char pin_left, char pin_right);
  void beep (signed char frequence);                   // effectue un beep a frequence
private:
  char p_pwm, p_left, p_right;
};
