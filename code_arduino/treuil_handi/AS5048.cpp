//lib pour capteur magnétique AS5048B : I2C
#include <Wire.h>

#define adr_pos1  255  // bits 6 à 13 (inverse dans la doc)
#define adr_pos2  254  // bits 0 à 5

void init_as5048(void)
{
  Wire.begin();        // join i2c bus (address optional for master)
  TWBR = 1;            // I2C max speed 
}

int read_as5048(char adr)
{
  int c;
  //recuperation du premier lot de bits
  Wire.beginTransmission(adr); // transmit to device 
  Wire.write(adr_pos2);             // envoit de l'adresse a lire 
  Wire.endTransmission();
  Wire.requestFrom(adr, 1);    // request bytes from slave 
  while(Wire.available())    // slave may send less than requested
  { 
    c = Wire.read(); // receive a byte as character
  }
  // recuperation du 2nd lot de bit et ajout au premier moyennant décallage
  Wire.beginTransmission(adr); // transmit to device 
  Wire.write(adr_pos1);             // envoit de l'adresse a lire  
  Wire.endTransmission();
  Wire.requestFrom(adr, 1);    // request bytes from slave 
  while(Wire.available())    // slave may send less than requested
  { 
    c += Wire.read() * 64; // receive a byte as character
  }
  return c;
}

