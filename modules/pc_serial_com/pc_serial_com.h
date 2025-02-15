//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_

//=====[Declaration of public defines]=========================================

#define UART_INTRO_KEY 0
#define UART_ENGINE_KEY 1
#define UART_ERROR_KEY 2

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void pcSerialComInit();
char pcSerialComCharRead();
void pcSerialComStringWrite( const char* str );
void pcSerialComUpdate();
bool pcSerialComCodeCompleteRead();
void pcSerialComCodeCompleteWrite( bool state );

void uartCommands(int cmd);

//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_