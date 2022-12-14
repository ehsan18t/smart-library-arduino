uint8_t rpwm = 10;
uint8_t lpwm = 11;

void setup() {
  pinMode(rpwm, OUTPUT);
  pinMode(lpwm, OUTPUT);

}

void loop() {
  right();
  delay(5000);
  left();
  delay(5000);

}


void right()
{
  digitalWrite(lpwm, LOW);
  digitalWrite(rpwm, HIGH);
}

void left()
{
  digitalWrite(rpwm, LOW);
  digitalWrite(lpwm, HIGH);
}