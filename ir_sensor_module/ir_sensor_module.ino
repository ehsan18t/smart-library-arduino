uint8_t ir_in_pin = 1;
uint8_t led_out_pin = 10;


void setup() {
  pinMode(ir_in_pin, INPUT);
  pinMode(led_out_pin, OUTPUT);
}

void loop() {
  if(digitalRead(ir_in_pin) == LOW)
    digitalWrite(led_out_pin, HIGH);
  else
    digitalWrite(led_out_pin, LOW);
  delay(10);
}
