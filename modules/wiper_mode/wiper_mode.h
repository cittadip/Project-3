#ifndef _WIPER_MODE_H_
#define _WIPER_MODE_H_

//=====[Declaration of public defines]=========================================

#define OFF_MODE 3
#define INT_MODE 4
#define LOW_MODE 5
#define HIGH_MODE 6

#define SHORT_DELAY 1000
#define MEDIUM_DELAY 4000
#define LONG_DELAY 10000

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

int WiperMode();
int IntDelay();
void WiperModeState();
void INT_State();
//=====[#include guards - end]=================================================

#endif // _WIPER_MODE_H_