
#include <Wire.h>
#define adr_enc1  64
#define adr_pos1  255  // 6 à 13 (inverse dans la doc)
#define adr_pos2  254  // 0 à 5

void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop()
{
  Wire.beginTransmission(adr_enc1); // transmit to device 
  Wire.write(adr_pos2);             // sends value byte  
  Wire.endTransmission();
  Wire.requestFrom(adr_enc1, 1);    // request bytes from slave 

  while(Wire.available())    // slave may send less than requested
  { 
    int c = Wire.read(); // receive a byte as character
    Serial.print("\nr:");
    Serial.print(c);         // print the character
  }
  delay(500);
}
