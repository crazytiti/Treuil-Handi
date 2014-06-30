class compteur
{
public:
  compteur(char adr_source, int adr_eeprom_source);      //constructeur avec adresse I2C et adresse de sauvegarde
  void init();             //init
  void raz();              //remise à 0
  float get_tour();        //detecte la position et compte le nombre de tour
private:
  char adr;                //adresse I2C
  signed int nb_tour;
  signed int pos, old_pos;
  int adr_eeprom;
};

