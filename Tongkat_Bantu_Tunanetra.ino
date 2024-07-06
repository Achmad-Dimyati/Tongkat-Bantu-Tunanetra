#include <Servo.h>

// Inisialisasi pin untuk sensor ultrasonik
const int sensor1TriggerPin = 2;
const int sensor1EchoPin = 3;
const int sensor2TriggerPin = 4;
const int sensor2EchoPin = 5;
const int sensor3TriggerPin = 6;
const int sensor3EchoPin = 7;

// Inisialisasi pin untuk servo motor
const int servoPin = 9;

// Inisialisasi objek Servo
Servo servo;
//MOTOR DC
const int mtrPin = 10;
const int mtrPin2 = 11;
void setup() {
  // Set up pin mode for sensor triggers
  pinMode(sensor1TriggerPin, OUTPUT);
  pinMode(sensor1EchoPin, INPUT);
  pinMode(sensor2TriggerPin, OUTPUT);
  pinMode(sensor2EchoPin, INPUT);
  pinMode(sensor3TriggerPin, OUTPUT);
  pinMode(sensor3EchoPin, INPUT);
  pinMode(mtrPin, OUTPUT);
  pinMode(mtrPin2, OUTPUT);
  
  // Set up servo
  servo.attach(servoPin);

  // Set initial servo angle
  servo.write(45);

  // Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read distances from sensors
  int distance1 = getDistance(sensor1TriggerPin, sensor1EchoPin);
  int distance2 = getDistance(sensor2TriggerPin, sensor2EchoPin);
  int distance3 = getDistance(sensor3TriggerPin, sensor3EchoPin);

  // Check distances and adjust servo angles
  if (distance1 < 50) {
    //servo.write(90);
    if (distance2 < distance3) {
    servo.write(0);
    digitalWrite(mtrPin, HIGH);
    digitalWrite(mtrPin2, HIGH);
    delay(500);
    } 
    if (distance2 > distance3) {
    servo.write(180);
    digitalWrite(mtrPin, HIGH);
    digitalWrite(mtrPin2, HIGH);
    delay(500);
    } 
  } 
  else {
    servo.write(90);  // Reset to initial angle
    digitalWrite(mtrPin, LOW);
    digitalWrite(mtrPin2, LOW);
  }

  // Output distances for debugging
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  Serial.print("Distance 2: ");
  Serial.println(distance2);
  Serial.print("Distance 3: ");
  Serial.println(distance3); 

  delay(500);  // Delay before next reading
}

int getDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  return distance;
}
