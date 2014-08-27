#include <Servo.h>
#include <arduino.h>

class moteur
{
public:
  void marche (signed char speed);                   //commande le moteur de -100% à +100%
  void init(char pin_servo, char pin_pwm, char pin_left, char pin_right);
private:
  char p_pwm, p_left, p_right;
};
