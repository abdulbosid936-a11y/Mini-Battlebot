#include <Servo.h> // ESC ni boshqarish uchun kutubxona

// Motor ulanishlari
const int IN1 = 6;
const int IN2 = 7;
const int IN3 = 9;
const int IN4 = 10;

// ESC ulanishi
Servo weaponESC;
const int weaponPin = 5; 

char command;
int speed = 0; // Qurol tezligi

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // ESC ni sozlash
  weaponESC.attach(weaponPin);
  weaponESC.writeMicroseconds(1000); // ESC ni faollashtirish (Arming)
  delay(2000); // ESC quvvatni tanib olishi uchun kutish

  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();

    switch (command) {  
      case 'F': forward();  break;
      case 'B': backward(); break;
      case 'L': left();     break;
      case 'R': right();    break;
      case 'S': stopMotors(); break;
      
      // Qurol (BLDC) boshqarish
      case 'W': weaponESC.writeMicroseconds(1500); break; // Yarim tezlik (Hujum!)
      case 'V': weaponESC.writeMicroseconds(2000); break; // Maksimal tezlik
      case 'w': weaponESC.writeMicroseconds(1000); break; // Qurolni to'xtatish
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}