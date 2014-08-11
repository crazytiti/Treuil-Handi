#include <Wire.h>

void init_as5048(void);      //init du bus
int read_as5048(char adr);   //renvoie la valeur de l'angle de 0 à 16383 (14 bits)
