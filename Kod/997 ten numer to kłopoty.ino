#include <SPI.H>

#define s1a 10
#define s1b 11
#define s2a 6
#define s2b 7
#define pwm1 9
#define pwm2 5

void setup() {
  Serial.begin(9600); // rozpocznij komunikacje z predkoscia 9600
  pinMode(s1a, OUTPUT);
  pinMode(s1b, OUTPUT);
  pinMode(s2a, OUTPUT);
  pinMode(s2b, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(pwm2, OUTPUT);
  
  digitalWrite(pwm1, LOW);
  digitalWrite(pwm2, LOW);
}

 
void loop() {
  delay(10);
  digitalWrite(pwm1, HIGH);
  digitalWrite(pwm2, HIGH);
  int i;
  
  while (Serial.available() > 0) { // sprawdcz czy jest jakas wartosc
    char wartosc = Serial.read(); // czytaj wartosc
    // analogWrite(9, wartosc); // jakas akcja inc...byte = <0,255> chyba xD
  if(wartosc<=85)
  {
    digitalWrite(s1a, LOW);
    digitalWrite(s1b, HIGH);
    digitalWrite(s2b, LOW);
    digitalWrite(s2a, HIGH);
    
  }
  else if(wartosc>85 && wartosc<=170)
  {
    digitalWrite(s1b, LOW);
    digitalWrite(s1a, HIGH);
    digitalWrite(s2b, LOW); 
    digitalWrite(s2a, HIGH);
    
  }
  else if(wartosc>170)
  {
    digitalWrite(s1b, LOW);
    digitalWrite(s1a, HIGH);
    digitalWrite(s2a, LOW);
    digitalWrite(s2b, HIGH);
  }
  }
  
}
