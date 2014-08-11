#include "eeprom.h"

void ee_ecrit(int adr, char* source, char nb)
{
  for (int i=0;i < nb; i++)
  {
    EEPROM.write(adr + i, source[i]);    
  }
}

void ee_lit(int adr, char* dest, char nb)
{
  for (int i=0;i < nb; i++)
  {
    dest[i] = EEPROM.read(adr + i);     
  }
}
