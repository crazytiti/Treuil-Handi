
class moteur
{
public:
  void marche (char sens, char speed);  //commande le moteur dans un certains sens (0 ou 1) et à une certaine vitesse (0 à 100%)
  void init(char pin);
};
