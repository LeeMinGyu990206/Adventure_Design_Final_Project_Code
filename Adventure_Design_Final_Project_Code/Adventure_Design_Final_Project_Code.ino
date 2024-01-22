#include <AFMotor.h>
#include <Servo.h>
#include "HX711.h"

#define calibration_factor - 7050.0
#define DOUT A5
#define CLK A1
HX711 scale(DOUT, CLK);

// Servo Motor: Cup Dispenser
Servo servo_CD1;
Servo servo_CD2;

// Spoon
Servo servo_SP;

// Stepper - Timing
AF_Stepper motor_ST(48, 1);

// DC Motor - Water Dispenser
AF_DCMotor motor_WD1(3);
AF_DCMotor motor_WD2(4);


int pos = 0;

// Step Motor: Timing Belt
// AF_DCMotor motor(200, 1);

// Relay Module: Powder, strip
int RP[] = {A2, A3, A4};
const int RP_size = sizeof(RP) / sizeof(RP[0]);
void setup()
{
  motor_WD1.run(RELEASE);
  motor_WD2.run(RELEASE);
  servo_SP.attach(A0);

  Serial.begin(9600);
  for(int i = 0; i < RP_size; i++){
    pinMode(RP[i], OUTPUT);
  }
  scale.set_scale(calibration_factor);
  scale.tare();
  Serial.println("Readings: ");

  motor_ST.setSpeed(150);

  for(int i = 0; i < RP_size; i++){
    digitalWrite(RP[i], HIGH);
  }
}
  // Cup  Dispenser
  Serial.println("Cup Dispenser");
  cup_dispenser();
  delay(1000);


// Servo Control
int cup_dispenser(){
    // sweeps from 0 degrees to 180 degrees
  servo_CD1.attach(9);
  servo_CD2.attach(10);


  // servo_CD1.write(0);
  // servo_CD2.write(180);

  // servo_CD1.write(180);
  // servo_CD2.write(0);

  for(pos = 0; pos <= 180; pos += 5) 
  {
    servo_CD1.write(pos);
    servo_CD2.write(180 - pos);  // 반대 방향으로 동작
    delay(15);
  }
  // sweeps from 180 degrees to 0 degrees
  for(pos = 180; pos >= 0; pos -= 5)
  {
    servo_CD1.write(pos);
    servo_CD2.write(180 - pos);  // 반대 방향으로 동작
    delay(15);
  }

  servo_CD1.detach();
  servo_CD2.detach();
}
// Water Pump

  ST_FORWARD(400); // Part A
  Serial.println("Powder");
  RP_ON(0, 1000);
  weight();
  weight();
  RP_ON(1, 1000);
  weight();
  weight();
// Step MOtor Contorl


int ST_FORWARD(int step, int dt){
  motor_ST.step(step, FORWARD, DOUBLE);
  delay(dt);
}

int ST_BACKWARD(int step, int dt){
  motor_ST.step(step, BACKWARD, DOUBLE);
  delay(dt);
}



// Control Relay Module - DC제어
int RP_ON(int idx, int delay_time){
  digitalWrite(RP[idx], LOW);
  Serial.print("Relay: ");
  Serial.println(idx);
  delay(delay_time);
  digitalWrite(RP[idx], HIGH);
  delay(500);
}
// Spin spoon
int Servo_spin(int rp_idx){

  // digitalWrite(A4, LOW);
  servo_SP.attach(A0);
  delay(15);

  Serial.print("SER_STATE 1");
  for(pos = 90; pos >= 0; pos -= 1) 
  {
    servo_SP.write(pos);
    delay(15);
  }
  delay(1000);
  delay(15);
  // digitalWrite(A4, HIGH);
  
  RP_ON(rp_idx, 5000);
  
  // digitalWrite(A4, LOW);
  delay(15);

  Serial.print("SER_STATE 2");
  for(pos = 0; pos <= 110; pos += 1) 
  {
    servo_SP.write(pos);
    delay(15);
  }
  servo_SP.detach();
  delay(15);
  // digitalWrite(A4, HIGH);

}
// Move FW(Backward)
int ST_FORWARD(int step){
  motor_ST.step(step, FORWARD, DOUBLE);
  delay(500);
}

int ST_BACKWARD(int step){
  motor_ST.step(step, BACKWARD, DOUBLE);
  delay(500);
}


// Servo Control
int cup_dispenser(){
    // sweeps from 0 degrees to 180 degrees
  servo_CD1.attach(9);
  servo_CD2.attach(10);


  // servo_CD1.write(0);
  // servo_CD2.write(180);

  // servo_CD1.write(180);
  // servo_CD2.write(0);

 
 for(pos = 0; pos <= 180; pos += 5) 
  {
    servo_CD1.write(pos);
    servo_CD2.write(180 - pos);  // 반대 방향으로 동작
    delay(15);
  }
  // sweeps from 180 degrees to 0 degrees
  for(pos = 180; pos >= 0; pos -= 5)
  {
    servo_CD1.write(pos);
    servo_CD2.write(180 - pos);  // 반대 방향으로 동작
    delay(15);
  }

  servo_CD1.detach();
  servo_CD2.detach();

}
// Spin spoon
int Servo_spin(int rp_idx){

  // digitalWrite(A4, LOW);
  servo_SP.attach(A0);
  delay(15);

  Serial.print("SER_STATE 1");
  for(pos = 90; pos >= 0; pos -= 1) 
  {
    servo_SP.write(pos);
    delay(15);
  }
  delay(1000);
  delay(15);
  // digitalWrite(A4, HIGH);
  
  RP_ON(rp_idx, 5000);
  
  // digitalWrite(A4, LOW);
  delay(15);

  Serial.print("SER_STATE 2");
  for(pos = 0; pos <= 110; pos += 1) 
  {
    servo_SP.write(pos);
    delay(15);
  }
  servo_SP.detach();
  delay(15);
  // digitalWrite(A4, HIGH);
}
