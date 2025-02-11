//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "display.h"
#include "ignition.h"
#include "pc_serial_com.h"
#include "servo.h"
#include "siren.h"
#include "user_interface.h"
#include "wiper_mode.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void SafeCarSystemInit()
{
    userInterfaceInit();
    pcSerialComInit();
    servoInit();
}

void SafeCarSystemUpdate()
{
    SERVO_LOW_MODE();
    /*userInterfaceUpdate();
    fireAlarmUpdate();    
    pcSerialComUpdate();
    eventLogUpdate();
    if 
    WiperModeState():
    INT_State();
    delay(SYSTEM_TIME_INCREMENT_MS);*/
}

//=====[Implementations of private functions]==================================
