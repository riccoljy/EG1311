#include <Servo.h>
Servo servo1;
Servo servo2;

int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
int MOTOR_PIN3 = 3;
int MOTOR_PIN4 = 11;
float SPEED_OF_SOUND = 0.0345;
int servo1_pin = 8;
//int servo2_pin = 4;
bool reachedwall;
long starttime;
int spintime_ms = 5000;
int microsecs;
float cms;
bool shot;


 void moveForward(){
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, HIGH);
    digitalWrite(MOTOR_PIN3, LOW);
    digitalWrite(MOTOR_PIN4, LOW);    
  }
  
  void moveForwardSlow(){
    analogWrite(MOTOR_PIN1, 200);
    analogWrite(MOTOR_PIN2, 200);
    analogWrite(MOTOR_PIN3, 0);
    analogWrite(MOTOR_PIN4, 0);

  }

  void moveBackward(){
    analogWrite(MOTOR_PIN1, 0);
    analogWrite(MOTOR_PIN2, 0);
    analogWrite(MOTOR_PIN3, 255);
    analogWrite(MOTOR_PIN4, 255); 
  }
  
  void rotate(){
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
    digitalWrite(MOTOR_PIN3, HIGH);
    digitalWrite(MOTOR_PIN4, LOW);
  }

  void shoot(){
    //servo1.write(90);
    //servo2.write(180);
    //delay(100);
    servo1.write(90);
    //servo2.write(0);
  }

  void stop(){
    analogWrite(MOTOR_PIN1, 0);
    analogWrite(MOTOR_PIN2, 0);
    analogWrite(MOTOR_PIN3, 0);
    analogWrite(MOTOR_PIN4, 0);   
  }

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(9600);

  servo1.attach(servo1_pin);
  servo1.write(180);
  // servo2.attach(servo2_pin);
  // servo2.write(180);

  reachedwall = false;
  shot = false;
  // put your setup code here, to run once:

}

// // ROTATE AFTER WALL
// void loop(){

//   if (reachedwall && !starttime) {
//     starttime = millis();
//     while (millis()-starttime < spintime_ms) rotate();
//   }  
//   moveForward();

//   digitalWrite(TRIG_PIN, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG_PIN, LOW);

//   int microsecs = pulseIn(ECHO_PIN, HIGH);
//   float cms = microsecs*SPEED_OF_SOUND/2;
//   //Serial.println(cms);
//   // Serial.print("reachedwall = ");
//   // Serial.print(reachedwall);
//   // Serial.print(" | rotating = ");
//   // Serial.print(rotating);
//   // Serial.print(" | starttime = ");
//   // Serial.println(starttime);
//   if (cms < 15) reachedwall = true;
// }

// REVERSE AFTER WALL
void loop() {
  // Serial.print("Time = ");
  // Serial.println(millis());
  // Serial.print("Reached wall?");
  // Serial.println(reachedwall? " Yes" : " No");


//UNCOMMENT
  microsecs = pulseIn(ECHO_PIN, HIGH);
  cms = microsecs*SPEED_OF_SOUND/2;
  cms = (cms>0) ? cms : -cms;

  // Serial.print("Distance = ");
  // Serial.println(cms);

  if (!reachedwall) {
    if (cms <12 && cms > 1 && millis() > 2000) {
      stop();
      delay(1000);
      shoot();
      delay(1000);
      servo1.write(180);
      reachedwall = true;
    }
    else moveForwardSlow();
  }
  else moveBackward();

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

}