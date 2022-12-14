uint8_t led = 11;
uint8_t sound = A5;
int threshold = 47;
uint8_t state = 0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(sound, INPUT);
}

void loop() {

  uint8_t soundses = analogRead(sound);
  if (soundses >= threshold)
  {
    if (state == 0)
    {
      Serial.println(sound);
      digitalWrite(led, HIGH);
      state = 1;
    }
    else
    {
      digitalWrite(led, LOW);
      state = 0;
    }
    delay(1000);
  }
}
