class compteur
{
public:
  compteur(void);
  void set_compteur(char adr_source, int adr_eeprom_source);      //adresse I2C et adresse de sauvegarde
  void init();             //init
  void raz();              //remise à 0
  float get_tour();        //detecte la position et compte le nombre de tour
private:  
  signed int nb_tour;
  signed int pos, old_pos;
  char adr;                //adresse I2C
  int adr_eeprom;
};

