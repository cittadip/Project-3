
//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void inputsInit();
void outputsInit();
void ignitionCase();
void driverIntroduction();
void drivingState();
void uartCommands(int cmd);

bool getDriverPresent();
bool getPassengerPresent();
bool getDriverSeatbelt();
bool getPassengerSeatbelt();
bool isignitionon();

void userInterfaceUpdate();

//=====[#include guards - end]=================================================

#endif // _IGNITION_H_