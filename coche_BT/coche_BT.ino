#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11); // RX | TX
#define IN1 8
#define IN2 9
#define ENA 4
#define IN3 6
#define IN4 7
#define ENB 5
String command = "";

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  BTserial.begin(9600);
}

void loop() {
  if (BTserial.available()) {
    command += BTserial.read();
    checkCommand(command);
  } else {
    command = "";
  }
}

void checkCommand (String check) {
  if (check.equalsIgnoreCase("117")) { // Delante
    leftMotorsStart(HIGH); // forward
    rightMotorsStart(LOW); // forward
  } else if (check.equalsIgnoreCase("100")) { // Atrás
    leftMotorsStart(LOW); // backward
    rightMotorsStart(HIGH); // backward
  } else if (check.equalsIgnoreCase("114")) { // Derecha
    leftMotorsStart(HIGH); // forward
    rightMotorsStart(HIGH); // backward
  } else if (check.equalsIgnoreCase("108")) { // Izquierda
    leftMotorsStart(LOW); // backward
    rightMotorsStart(LOW); // forward
  } else if (check.equalsIgnoreCase("115")) { // Parar
    motorsStop();
  } else if (check.equalsIgnoreCase("120")) { // Sirena
    // This is just for fun !!
    tone(3, 440, 100);
    delay(100);
    tone(3, 415, 100);
    delay(100);
    tone(3, 440, 100);
    delay(100);
    tone(3, 415, 100);
    delay(100);
    tone(3, 440, 100);
    delay(100);
    tone(3, 375, 150);
    delay(150);
    tone(3, 440, 150);
    delay(150);
    tone(3, 494, 250);
    delay(250);
  }
}

// Direction = HIGH -> backward; LOW -> forward
void leftMotorsStart(boolean dir) {
  digitalWrite(ENA, 1);
  digitalWrite(IN1, dir);
  digitalWrite(IN2, !dir);
}

// Direction = HIGH -> forward; LOW -> backward
void rightMotorsStart(boolean dir) {
  digitalWrite(ENB, 1);
  digitalWrite(IN3, dir);
  digitalWrite(IN4, !dir);
}

void motorsStop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
