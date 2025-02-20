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


#define DUTY_ZERO 25//25
#define DUTY_67 80//68


#define SMALL_DELAY 3000
#define MEDIUM_DELAY 6000
#define LONG_DELAY 8000


#define LOW_TURN_TIME 3000
#define SERVO_STEP_TIME 50
int angle_increment;
int time_incrament_two = 0;
bool went_down = false;
bool went_up = false;


// UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

PwmOut servo(PF_9);

int servo_update_time;
float angle;
int servo_step_time;
int wait_time;
ServoMode servo_mode;


void servoInit(){
   servo.period(PERIOD);
   servo.write(DUTY_ZERO);
   servo_update_time = 0;
   angle = DUTY_ZERO;
   servo_step_time = 10;
}

void SERVO_OFF_MODE() {
   servo_mode = OFF_M;
}

void SERVO_INT_MODE() {  //30 rev
   servo_mode = INT_M;
}

void SERVO_LOW_MODE() {  //30 rev
   servo_mode = LOW_M;
}
void SERVO_HIGH_MODE() {
   servo_mode = HIGH_M;
}

void SERVO_MODE_OFF(){
   servo_mode = OFF_M;
}




void INT_3_MODE() {
   servo_mode = INT_3_M;
}
void INT_6_MODE() {
   servo_mode = INT_6_M;
}
void INT_8_MODE() {
   servo_mode = INT_8_M;
}

int getAngle(){
    return angle;
}

void set_servo_step_time() {
   switch(servo_mode){
       case OFF_M :
           break;
       //case INT_M :
           //break;
       case HIGH_M :
            angle_increment = 3;
            wait_time = 0;
            break;

       case LOW_M :
            angle_increment = 1;
            wait_time = 0;
            break;

       case INT_3_M:
            angle_increment = 1;
            wait_time = 3000;
            break;

       case INT_6_M:
            angle_increment = 1;
            wait_time = 6000;
            break;

       case INT_8_M:
            angle_increment = 1;
            wait_time = 9000;
            break;
   }
}


// went_down = false;
// went_up = false;
// time_incrament_two = 0;

void servo_update_function(){
    set_servo_step_time();

    if (servo_mode != OFF_M) {

        //increment servo update time
        servo_update_time = servo_update_time + SYSTEM_TIME_INCREMENT_MS ;
        time_incrament_two = time_incrament_two + SYSTEM_TIME_INCREMENT_MS;


        if (servo_update_time >= SERVO_STEP_TIME){    //only move servo once per servo_step_time (must be > 20ms)

            if (went_down == true && went_up == true) {
                if ( wait_time <= time_incrament_two ) {
                    went_down = false;
                    went_up = false;
                } else {
                    time_incrament_two = 0;
                }
            } else {
                
                servo.write(angle/1000);
                //increse angle if too low
                if (angle <= DUTY_67){
                    angle = angle + angle_increment;//Increment position by 2 degrees 
                    //(you need to convert this to duty cycle increment)
                    went_down = true;

                    //decrese angle if too high
                } else if (angle > DUTY_67) {
                    angle = angle - DUTY_ZERO;//angle + angle_increment;
                    went_up = true;

                //in case of error reset system
                } else {
                    angle = DUTY_ZERO;
                }
            }
            //reset servo update time
            servo_update_time = 0;
        }
        
    } else { // if it is off set pos to zero
        servo.write(DUTY_ZERO);
    }
}


