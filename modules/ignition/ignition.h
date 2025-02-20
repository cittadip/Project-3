
//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

#include "mbed.h"
#include "arm_book_lib.h"
//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void ignitionUpdate();
void driverIntroduction();
void drivingState();
void uartCommands(int cmd);

bool getDriverPresent();
bool getPassengerPresent();
bool getDriverSeatbelt();
bool getPassengerSeatbelt();
bool isignitionon();

void userInterfaceUpdate();
bool getEngineState();

typedef enum {
    BUTTON_OFF_0,
    BUTTON_ON_1,
    BUTTON_READY_STATE,
    BUTTON_ON_2
} ignitionState_t;

extern ignitionState_t ignition_State;



//=====[#include guards - end]=================================================

#endif // _IGNITION_H_
