#include <EEPROM.h>

void ee_ecrit(int adr, char* source, char nb)
// écrit nb octet depuis source vers adr en eeprom
{
  for (int i=0;i < nb; i++)
  {
    EEPROM.write(adr + i, source[i]);    
  }
}

void ee_lit(int adr, char* dest, char nb)
//lit nb octet en eeprom vers dest
{
  for (int i=0;i < nb; i++)
  {
    dest[i] = EEPROM.read(adr + i);     
  }
}
