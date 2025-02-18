#include "servo.h"
#include "wiper_mode.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "safe_car_system.h"

#define PERIOD 0.02
#define STOP_PERIOD 1.5
#define DUTY_STOP 0.075
#define DUTY_HIGH 0.065
#define DUTY_LOW 0.0250
#define DUTY_BACK 0.080

#define DUTY_ZERO 0.025

#define SMALL_DELAY 3000
#define MEDIUM_DELAY 6000
#define LONG_DELAY 8000

#define LOW_TURN_TIME 3000
//#define STEP_TIME 
// #define LOW_TURN_TIME 6000
// #define LONG_DELAY 8000

PwmOut servo(PF_9);

int servo_update_time;
int angle;
int servo_step_time;
ServoMode servo_mode;

void set_servo_step_time();

void servoInit(){
    servo.period(PERIOD);
    servo.write(DUTY_ZERO);
<<<<<<< HEAD
    servo_update_time = 0;
    angle = 0;
    servo_step_time = 10;
=======
>>>>>>> 9f36f9a79a92476e9b886792d5a51f00e5f6d7fd
}


void SERVO_OFF_MODE() {
<<<<<<< HEAD
    servo_mode = OFF_M;
    /*servo.write(DUTY_STOP);
=======
>>>>>>> 9f36f9a79a92476e9b886792d5a51f00e5f6d7fd
    delay(SMALL_DELAY);
    servo.write(DUTY_STOP);
    delay(LOW_TURN_TIME);*/
}
void SERVO_INT_MODE() {  //30 rev
    servo_mode = INT_M;
    /*servo.write(DUTY_LOW);
    delay(LOW_TURN_TIME);
    servo.write(DUTY_BACK);
    delay(LOW_TURN_TIME);*/
}

void SERVO_LOW_MODE() {  //30 rev
    servo_mode = LOW_M;
    /*servo.write(DUTY_LOW);  
    delay(LOW_TURN_TIME);
    servo.write(DUTY_BACK);
    delay(LOW_TURN_TIME);*/
}
void SERVO_HIGH_MODE() {
    servo_mode = HIGH_M;
    /*servo.write(0.025);
    delay(750);
    servo.write(0.057);
    delay(750);*/
}

void SERVO_MODE_OFF(){
    servo_mode = OFF_M;
    /*servo.period(PERIOD);
    servo.write(DUTY_LOW);*/
}


void INT_3_MODE() {
    //delay(SMALL_DELAY);
    servo_mode = INT_3_M;
}
void INT_6_MODE() {
    //delay(MEDIUM_DELAY);
    servo_mode = INT_6_M;
}
void INT_8_MODE() {
    //delay(LONG_DELAY);
    servo_mode = INT_8_M;
}

void set_servo_step_time() {
    switch(servo_mode){
        case OFF_M :
            servo_step_time = 20;
        case INT_M :
            servo_step_time = 20;
        case HIGH_M :
            servo_step_time = 40;
        case LOW_M :
            servo_step_time = 20;
        case INT_3_M:
            servo_step_time = 20;
        case INT_6_M:
            servo_step_time = 20;
        case INT_8_M:
            servo_step_time = 20;
    }
}

//*
void servo_update_function(){
    set_servo_step_time();
    servo_update_time = servo_update_time + SYSTEM_TIME_INCREMENT_MS ; 
    if (servo_update_time == servo_step_time){    //only move servo once per servo_step_time (must be > 20ms)
        servo.write(angle);
        angle = angle+(2/180) ;                                  //Increment position by 2 degrees (you need to convert this to duty cycle increment)
        servo_update_time = 0 ;
    }
} //*/