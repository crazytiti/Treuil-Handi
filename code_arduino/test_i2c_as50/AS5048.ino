//lib pour capteur magnétique AS5048B : I2C
#include <Wire.h>

#define adr_pos1  255  // 6 à 13 (inverse dans la doc)
#define adr_pos2  254  // 0 à 5

void init_as5048(void)
//init du bus
{
 Wire.begin();        // join i2c bus (address optional for master)
 TWBR = 1;            // I2C max speed 
}
  
int read_as5048(char adr)
//renvoie la valeur de l'angle de 0 à 16383 (14 bits)
{
  int c;
  
  Wire.beginTransmission(adr); // transmit to device 
  Wire.write(adr_pos2);             // sends value byte  
  Wire.endTransmission();
  Wire.requestFrom(adr, 1);    // request bytes from slave 
  while(Wire.available())    // slave may send less than requested
  { 
    c = Wire.read(); // receive a byte as character
  }
  Wire.beginTransmission(adr); // transmit to device 
  Wire.write(adr_pos1);             // sends value byte  
  Wire.endTransmission();
  Wire.requestFrom(adr, 1);    // request bytes from slave 
  while(Wire.available())    // slave may send less than requested
  { 
    c += Wire.read() * 64; // receive a byte as character
  }
  return c;
}
