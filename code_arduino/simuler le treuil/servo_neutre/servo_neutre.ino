#include <Servo.h>
Servo myservo;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  myservo.attach (11);                   // choix pin du servo
  myservo.write (90);                    // Set servo à mi-parcours
  pinMode(13, OUTPUT); //LED on Model A   
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW); 
  delay(300);  
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW); 
  delay(300);    
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW); 
  delay(300);               
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW); 
  delay(3000);     
  
   digitalWrite(13, HIGH);
  delay(200);
 
  digitalWrite(13, LOW); 
  delay(2000);    
}
