//=====[#include guards - begin]===============================================

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    IDLE,
    SOLO_LECTURA
} system_mode_t;

//=====[Declarations (prototypes) of public functions]=========================

void system_init();
void system_update();

//=====[#include guards - end]=================================================

#endif // _SYSTEM_H_