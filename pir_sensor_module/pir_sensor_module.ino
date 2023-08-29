uint8_t pir_in = 10;
uint8_t out = 9;


void setup() {
  pinMode(pir_in, INPUT);
  pinMode(out, OUTPUT);

}

void loop() {
  digitalWrite(out, digitalRead(pir_in));
}
