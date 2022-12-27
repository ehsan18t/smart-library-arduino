// Thermal Sensor
uint8_t pir_in = 10;
uint8_t out = 9;
// Slound Sensor
uint8_t sound_out = 0;
uint8_t sound = A5;
uint8_t threshold = 47;
uint8_t state = 0;
uint8_t count = 0;


void setup() {
  pinMode(pir_in, INPUT);
  pinMode(out, OUTPUT);
  
  pinMode(sound, INPUT);
  pinMode(sound_out, OUTPUT);

}

void loop() {
  digitalWrite(out, digitalRead(pir_in));

  // uint8_t soundses = analogRead(sound);
  // if (soundses >= threshold)
  // {
  //   count++;
  //   if (count > 3)
  //   {
  //     digitalWrite(sound_out, HIGH);
  //     delay(10000);
  //     count = 0;
  //   }
  // }
}
