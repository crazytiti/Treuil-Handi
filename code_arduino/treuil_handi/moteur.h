#include <Servo.h>
#include <arduino.h>

class moteur
{
public:
  void marche (signed char speed);                   //commande le moteur de -100% à +100%
  void init(char pin_servo, char pin_pwm1, char pin_pwm2);
private:
  char p_pwm1, p_pwm2;
};
