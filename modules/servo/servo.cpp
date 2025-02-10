#include "servo.h"
#include "wiper_mode.h"
#include "arm_book_lib.h"
#include "mbed.h"

#define PERIOD 2000
#define STOP_PERIOD 1.5
#define DUTY_STOP 0.075
#define DUTY_HIGH 0.065
#define DUTY_LOW 0.070
#define DUTY_BACK 0.080

PwmOut servo(PF_9);



void SERVO_OFF_MODE() {
  servo.period(STOP_PERIOD);
  servo.write(DUTY_STOP);
  
}
void SERVO_INT_MODE() {
  servo.period(PERIOD);
  servo.write(DUTY_LOW);
  servo.write(DUTY_BACK);
}
void SERVO_LOW_MODE() {
 servo.period(PERIOD);
  servo.write(DUTY_LOW);
  servo.write(DUTY_BACK);
}
void SERVO_HIGH_MODE() {
  servo.period(PERIOD);
  servo.write(DUTY_HIGH);
  servo.write(DUTY_BACK);
}


while 
void SHORT_MODE();
    

void MEDIUM_MODE();


void LONG_MODE();

 

void SERVO_RUN( int delay, bool HI ) {

    // move to 180

    // move to 0


    //delay because 




}