#include <IRremote.h>
#define IN1  8
#define IN2  9
#define ENA  11
#define IN3  6
#define IN4  7
#define ENB  10
#define CH1  2
#define CH2  3
#define CH3  4

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
}

void loop() {
  int eje_x = pulseIn(CH1, HIGH);
  int eje_y = pulseIn(CH2, HIGH);
  int eje_x2 = pulseIn(CH3, HIGH);
  if (eje_y > 1700) { // Arriba
    leftMotorsStart(HIGH); // forward
    rightMotorsStart(LOW); // forward
  } else if (eje_y < 1200) { // Atrás
    leftMotorsStart(LOW); // backward
    rightMotorsStart(HIGH); // backward
  } else if (eje_x > 1700) { // Derecha
    leftMotorsStart(HIGH); // forward
    rightMotorsStart(HIGH); // backward
  } else if (eje_x < 1200) { // Izquierda
    leftMotorsStart(LOW); // backward
    rightMotorsStart(LOW); // forward
  } else {
    motorsStop();
  }
}

// Direction = HIGH -> backward; LOW -> forward
void leftMotorsStart(boolean dir)
{
  digitalWrite(ENA, 1);
  digitalWrite(IN1, dir);
  digitalWrite(IN2, !dir);
}

// Direction = HIGH -> forward; LOW -> backward
void rightMotorsStart(boolean dir)
{
  digitalWrite(ENB, 1);
  digitalWrite(IN3, dir);
  digitalWrite(IN4, !dir);
}

void motorsStop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
