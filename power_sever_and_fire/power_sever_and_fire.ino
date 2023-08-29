#include<NewPing.h>
// Sonar Sensor
int trigPin1 = A0;
int echoPin1 = A1;
int trigPin2 = A2;
int echoPin2 = A3;
int led = 5;
int fan = 6;
#define ALARM 9  // pin 9 for Alarm
#define FLAME 8 // connect DO pin of sensor to this pin

// Sonar
int max_distance = 7;
NewPing sonar1(trigPin1, echoPin1, max_distance);
NewPing sonar2(trigPin2, echoPin2, max_distance);

void setup() {
  Serial.begin(9600);
  Serial.println("Library Fire Module Test");
   
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);

  pinMode(FLAME, INPUT);//define FLAME input pin
  pinMode(ALARM, OUTPUT);//define ALARM output pin
}

void loop() {

  int fire = digitalRead(FLAME);// read FLAME sensor

  if( fire == HIGH){
    digitalWrite(ALARM,HIGH);// set the buzzer ON
    Serial.println("Fire! Fire!");
  }
  else{
    digitalWrite(ALARM,LOW); // Set the buzzer OFF
    Serial.println("Peace");

  }
 if (sonar1.ping_cm() > 0 || sonar2.ping_cm() > 0)
  {
    digitalWrite(led, HIGH);
    digitalWrite(fan, LOW);
    Serial.println("Detected");
  }
  else {
    digitalWrite(led, LOW);
    digitalWrite(fan, HIGH);
    Serial.println("Not Detected");
  }

  delay(1000);
}
