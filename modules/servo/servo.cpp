#include "servo.h"
#include "wiper_mode.h"
#include "arm_book_lib.h"
#include "mbed.h"

#define PERIOD 0.02
#define STOP_PERIOD 1.5
#define DUTY_STOP 0.075
#define DUTY_HIGH 0.065
#define DUTY_LOW 0.070
#define DUTY_BACK 0.080

#define SMALL_DELAY 3000
#define MEDIUM_DELAY 6000
#define LONG_DELAY 8000

#define LOW_TURN_TIME 3000
// #define LOW_TURN_TIME 6000
// #define LONG_DELAY 8000

PwmOut servo(PF_9);



void servoInit(){
    servo.period(PERIOD);
}


void SERVO_OFF_MODE() {
    // servo.period(STOP_PERIOD);
    delay(SMALL_DELAY);
    servo.write(DUTY_STOP);
    delay(LOW_TURN_TIME);
}
void SERVO_INT_MODE() {
    servo.write(DUTY_LOW);
    delay(LOW_TURN_TIME);
    servo.write(DUTY_BACK);
}

void SERVO_LOW_MODE() {
    servo.write(DUTY_LOW);
    delay(LOW_TURN_TIME);
    servo.write(DUTY_BACK);
    delay(LOW_TURN_TIME);
}
void SERVO_HIGH_MODE() {
    servo.write(DUTY_HIGH);
    delay(LOW_TURN_TIME);
    servo.write(DUTY_BACK);
}


void SHORT_MODE() {
    delay(SMALL_DELAY);
}
void MEDIUM_MODE() {
    delay(MEDIUM_DELAY);
}
void LONG_MODE() {
    delay(LONG_DELAY);
}