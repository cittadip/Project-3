//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "siren.h"

#include "smart_home_system.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut sirenPin(PE_10);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool sirenState = OFF;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void sirenInit()
{
    sirenPin = ON;

    sirenPin.mode(OpenDrain);
    sirenPin.input();
}

bool sirenStateRead()
{
    return sirenState;
}

void sirenStateWrite( bool state )
{
    sirenState = state;
}

//this might be able to go away? - read over to understand what its doing and check to see if its used anywhere else in your system
void sirenUpdate( int strobeTime )
{
    static int accumulatedTimeAlarm = 0;
    accumulatedTimeAlarm = accumulatedTimeAlarm + SYSTEM_TIME_INCREMENT_MS;
    
    if( sirenState ) {
        if( accumulatedTimeAlarm >= strobeTime ) {
                accumulatedTimeAlarm = 0;
                sirenPin= !sirenPin;
        }
    } else {
        sirenPin = ON;
    }
}

void sirenON(){
    sirenPin.output();
    sirenPin = LOW;
}

void sirenOFF(){
    sirenPin.input();
    sirenPin = HIGH;
}

//=====[Implementations of private functions]==================================

