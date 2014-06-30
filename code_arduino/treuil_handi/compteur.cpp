#include "AS5048.h"
#include "eeprom.h"
#include "compteur.h"

compteur::compteur(void)
{
}

void compteur::set_compteur(char adr_source, int adr_eeprom_source)
{
  adr = adr_source;
  adr_eeprom = adr_eeprom_source;
}

void compteur::init()
{
  init_as5048();                            //initialisation as5048
  pos = read_as5048(adr);                   //position actuelle
  old_pos = pos;                            //mise ne mémoire pour detection d'un tour complet
  ee_lit(adr_eeprom, (char*)&nb_tour, 4);   //récupere le nombre de tour en eeprom
}

void compteur::raz()
//remet à 0 le compteur de nombre de tour en eeprom
{
  nb_tour = 0;
  ee_ecrit(adr_eeprom, (char*)&nb_tour, 4);
  pos = read_as5048(adr);
  old_pos = pos;
}

float compteur::get_tour()
{
  float r;
  pos = read_as5048(adr);
  if (pos - old_pos > 8191)
  {
    nb_tour -=1;
    ee_ecrit(adr_eeprom, (char*)&nb_tour, 4);
  }
  if (old_pos - pos > 8191)
  {
    nb_tour +=1;
    ee_ecrit(adr_eeprom, (char*)&nb_tour, 4);
  }
  old_pos = pos;

  r = pos;
  r = nb_tour + r / 16383;
  return r;
}

