#include <Servo.h>

/* ================== SENZORI FLACARA ================== */
#define FLAME_SENSOR_LEFT    A0
#define FLAME_SENSOR_CENTER  A1
#define FLAME_SENSOR_RIGHT   A2

/* ================== L298N ================== */
#define IN1 5
#define IN2 6
#define IN3 9
#define IN4 10
#define ENA 4
#define ENB 8

/* ================== ALTE COMPONENTE ================== */
#define RELAY_PIN 7
#define SERVO_PIN 3
#define TRIG_PIN 11
#define ECHO_PIN 12

/* ================== CONSTANTE ================== */
#define FIRE_THRESHOLD 300
#define STOP_DISTANCE 30

#define BASE_SPEED 170
#define TURN_SPEED 140

#define RELAY_ON  LOW   // LOW -> pompa pornita
#define RELAY_OFF HIGH  // HIGH -> pompa oprita

Servo waterServo;

/* ================== SETUP ================== */
void setup() {
  Serial.begin(9600);

  // Motoare
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT); pinMode(ENB, OUTPUT);

  // Releu pompa
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, RELAY_OFF); // Pompa oprita la start

  // Ultrasonic
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Senzori flacara
  pinMode(FLAME_SENSOR_LEFT, INPUT);
  pinMode(FLAME_SENSOR_CENTER, INPUT);
  pinMode(FLAME_SENSOR_RIGHT, INPUT);

  // Servo
  waterServo.attach(SERVO_PIN);
  waterServo.write(90);  // pozitie neutra

  stopMotors();

  Serial.println("🔥 Fire Fighting Robot READY");
}

/* ================== LOOP ================== */
void loop() {
  int flameLeft   = analogRead(FLAME_SENSOR_LEFT);
  int flameCenter = analogRead(FLAME_SENSOR_CENTER);
  int flameRight  = analogRead(FLAME_SENSOR_RIGHT);

  long distance = readUltrasonic();

  Serial.print("L:"); Serial.print(flameLeft);
  Serial.print(" C:"); Serial.print(flameCenter);
  Serial.print(" R:"); Serial.print(flameRight);
  Serial.print(" | D:"); Serial.println(distance);

  bool fireDetected = false;

  // 🔥 Detectare foc
  if (flameCenter < FIRE_THRESHOLD || flameLeft < FIRE_THRESHOLD || flameRight < FIRE_THRESHOLD) {
    fireDetected = true;

    // Daca e aproape, opreste robotul si porneste pompa
    if (distance <= STOP_DISTANCE) {
      stopMotors();
      activateWaterPump();
    } else {
      // Miscare in functie de senzor
      if (flameCenter < FIRE_THRESHOLD) moveForward(BASE_SPEED / 2); // viteza mai mica aprox
      else if (flameLeft < FIRE_THRESHOLD) turnLeft(TURN_SPEED / 2);
      else if (flameRight < FIRE_THRESHOLD) turnRight(TURN_SPEED / 2);

      deactivateWaterPump(); // doar la distanta mica porneste pompa
    }
  }

  // ❌ Niciun foc
  if (!fireDetected) {
    stopMotors();
    deactivateWaterPump();
  }
}

/* ================== ULTRASONIC ================== */
long readUltrasonic() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 999;

  return duration * 0.034 / 2;
}

/* ================== MISCARE ================== */
void moveForward(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void turnLeft(int speed) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void turnRight(int speed) {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
  analogWrite(ENA, speed); analogWrite(ENB, speed);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}

/* ================== APA + SERVO ================== */
void activateWaterPump() {
  Serial.println("🚰 PUMP ON");
  digitalWrite(RELAY_PIN, RELAY_ON);

  // Servo SG90 miscarea sigură (~100°)
  for (int pos = 40; pos <= 140; pos += 2) {
    waterServo.write(pos);
    delay(20);
  }
  for (int pos = 140; pos >= 40; pos -= 2) {
    waterServo.write(pos);
    delay(20);
  }
}

void deactivateWaterPump() {
  digitalWrite(RELAY_PIN, RELAY_OFF);
  waterServo.write(90); // pozitie neutra
}
