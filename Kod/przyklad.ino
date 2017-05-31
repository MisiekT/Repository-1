void setup() {
  Serial.begin(9600); // rozpocznij komunikacje z predkoscia 9600
  pinMode(9, OUTPUT);
}

 
void loop() {
  delay(10);
  while (Serial.available() > 0) { // sprawdcz czy jest jakas wartosc
    char wartosc = Serial.read(); // czytaj wartosc
    analogWrite(9, wartosc); // jakas akcja inc...byte = <0,255> chyba xD
  }
}
