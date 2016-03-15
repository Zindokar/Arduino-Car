#include <IRremote.h>
#define IN1  8
#define IN2  9
#define ENA  11
#define IN3  6
#define IN4  7
#define ENB  10
IRrecv irrecv(3);
decode_results results;

void setup()
{
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}
/**
 * LG IR Code
 * ----------------
 * UP : 20df02fd
 * DOWN : 20df827d
 * RIGHT : 20df609f
 * LEFT : 20dfe01f
 * OK : 20df22dd
 */
void loop() {
  if (irrecv.decode(&results)) {
    if (code.equalsIgnoreCase("20df02fd")) { // UP
      leftMotorsStart(HIGH); // forward
      rightMotorsStart(LOW); // forward
      Serial.println("UP");
    } else if (code.equalsIgnoreCase("20df827d")) { // DOWN
      leftMotorsStart(LOW); // backward
      rightMotorsStart(HIGH); // backward
      Serial.println("DOWN");
    } else if (code.equalsIgnoreCase("20df609f")) { // RIGHT
      leftMotorsStart(HIGH); // forward
      rightMotorsStart(HIGH); // backward
      Serial.println("RIGHT");
      delay(150);
      motorsStop();
    } else if (code.equalsIgnoreCase("20dfe01f")) { // LEFT
      leftMotorsStart(LOW); // backward
      rightMotorsStart(LOW); // forward
      delay(150);
      motorsStop();
    } else if (code.equalsIgnoreCase("20df22dd")) { // OK
      motorsStop();
    }
    irrecv.resume();
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
