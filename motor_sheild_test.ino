#include <AFMotor.h>
#include "IRremote.h"

int receiver = A0;           // IR pin
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
AF_DCMotor motor3(3);        // Sets up motor 3
AF_DCMotor motor4(4);        // Sets up motor 4

// Global Variables
char input = '-';
int forwardNum = 0;
int backwardNum = 0;
int leftNum = 0;
int rightNum = 0;
void setup() {
  // Sets motor Speed
  int motorSpeed = 2000;
  motor3.setSpeed(motorSpeed);
  motor4.setSpeed(motorSpeed);
  Serial.begin(9600);  // Begins Serial
  irrecv.enableIRIn(); // Start the receiver
}

void translateIR()
{
  switch (results.value)
  {
    case 0xFF629D: forward(); break;
    case 0xFF22DD: right();  break;
    case 0xFFC23D: left(); break;
    case 0xFFA857: backward();   break;
    default:
      Serial.println(" other button : ");
      Serial.println(results.value);
  }
  delay(500);
}
/**
   Motor Functions
   forward backward left right and release
*/
void forward() {
  if (isEven(forwardNum)){
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }
  else {
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
  forwardNum++;
}
void backward() {
  if (isEven(backwardNum)){
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
  else {
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
  backwardNum++;
}
void left() {
  motor3.run(RELEASE);
   motor4.run(RELEASE);
  if (isEven(leftNum)){
    motor3.run(BACKWARD);
  }
  else {
    motor3.run(RELEASE);
  }
  leftNum++;
}
void right() {
  motor3.run(RELEASE);
   motor4.run(RELEASE);
  if (isEven(rightNum)){
    motor4.run(BACKWARD);
  }
  else {
    motor4.run(RELEASE);
  }
  rightNum++;
}
void releaseMotor(){
  Serial.println("Release motors");
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
int isEven(int num)
{
  return !(num & 1);

}
void loop() {
  // Get ir input
  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume(); // receive the next value
  }
}
