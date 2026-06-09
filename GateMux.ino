// Pin Configuration
const int pinX = 2; // PD2
const int pinY = 3; // PD3
const int pinZ = 4; // PD4
const int pinF = 13; // PB5 (Onboard LED)

void setup() {
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  pinMode(pinZ, INPUT);
  pinMode(pinF, OUTPUT);
}

void loop() {
  bool X = digitalRead(pinX);
  bool Y = digitalRead(pinY);
  bool Z = digitalRead(pinZ);
  
  // Implemented Multiplexer Logic Formula: F = XY + Y'Z
  bool F = (X && Y) || (!Y && Z);
  
  digitalWrite(pinF, F);
}
