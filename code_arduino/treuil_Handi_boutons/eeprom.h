#include <EEPROM.h>

void ee_ecrit(int adr, char* source, char nb);    // écrit nb octets depuis source vers adr en eeprom
void ee_lit(int adr, char* dest, char nb);        //lit nb octets en eeprom vers dest
