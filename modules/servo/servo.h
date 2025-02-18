#ifndef _SERVO_H_
#define _SERVO_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void servoInit();
void SERVO_OFF_MODE();
void SERVO_INT_MODE();
void SERVO_LOW_MODE();
void SERVO_HIGH_MODE();
  
void SHORT_MODE();
void MEDIUM_MODE();
void INT_State();
void LONG_MODE();



typedef enum {
    LOW_M,
    INT_M,
    HIGH_M,
    OFF_M,
    INT_3_M,
    INT_6_M,
    INT_8_M
} ServoMode;

void servo_update_function();

//=====[#include guards - end]=================================================

#endif // _WIPER_MODE_H_