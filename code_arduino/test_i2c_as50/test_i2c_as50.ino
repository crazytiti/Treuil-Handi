

#define adr_enc1  64
#define adr_eeprom_nb_tour  0

void setup()
{
  init_as5048();
  Serial.begin(9600);  // start serial for output
}

void loop()
{
 float r;
 signed int nb_tour;
 signed int pos, old_pos;
 //init
 ee_lit(adr_eeprom_nb_tour, (char*)&nb_tour, 4);
 pos = read_as5048(adr_enc1);
 old_pos = pos;
 
 while(1)
 {
   pos = read_as5048(adr_enc1);
   if (pos - old_pos > 8191)
   {
     nb_tour -=1;
     ee_ecrit(adr_eeprom_nb_tour, (char*)&nb_tour, 4);
   }
   if (old_pos - pos > 8191)
   {
     nb_tour +=1;
     ee_ecrit(adr_eeprom_nb_tour, (char*)&nb_tour, 4);
   }
   old_pos = pos;
   
   r = pos;
   r = nb_tour + r / 16383;
   Serial.print("\nr:");
   Serial.print(r);
   delay(20);
 }
}
