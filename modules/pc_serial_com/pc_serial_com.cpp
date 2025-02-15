//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "pc_serial_com.h"

//uart macros

typedef enum{
    PC_SERIAL_COMMANDS,
    PC_SERIAL_GET_CODE,
    PC_SERIAL_SAVE_NEW_CODE,
} pcSerialComMode_t;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


//=====[Declaration and initialization of private global variables]============

static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;
static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void pcSerialComStringRead( char* str, int strLength );

static void pcSerialComGetCodeUpdate( char receivedChar );
static void pcSerialComSaveNewCodeUpdate( char receivedChar );

static void pcSerialComCommandUpdate( char receivedChar );

static void availableCommands();




void pcSerialComInit();
char pcSerialComCharRead();
void pcSerialComStringWrite( const char* str );
void pcSerialComUpdate();
void uartCommands(int cmd);


//=====[Implementations of public functions ===================================

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
// UART interface for communication with a computer or external device
// USBTX and USBRX represent transmit and receive pins, respectively
// 115200 is the baud rate for serial communication


/*
a list of UART serial prints depending on the situation the car is in
@param cmd the uart that is selected to be printed
*/
void pcSerialComInit()
{
    // availableCommands();
}

void uartCommands(int cmd) 
{
  /*switch (cmd) {
  case UART_INTRO_KEY:
    uartUsb.write("\nWelcome to enhanced alarm system model 218-W24", 46);
    break;

  case UART_ENGINE_KEY:
    uartUsb.write("\nEngine started.", 15);
    break;
  case UART_ERROR_KEY:
    uartUsb.write("\nIgnition inhibited", 19);
    uartUsb.write("\nReasons:", 9);

    if (!getDriverPresent()) {
      uartUsb.write("\nDriver not present.", 20);
    }
    if (!getPassengerPresent()) {
      uartUsb.write("\nPassenger not present.", 23);
    }
    if (!getDriverSeatbelt()) {
      uartUsb.write("\nDriver Seatbelt not fastened.", 30);
    }
    if (!getPassengerSeatbelt()) {
      uartUsb.write("\nPassenger Seatbelt not fastened.", 33);
    }
    break;
  }*/
}




char pcSerialComCharRead()
{
    char receivedChar = '\0';
    return receivedChar;
}

void pcSerialComStringWrite( const char* str )
{
    // uartUsb.write( str, strlen(str) );
}

void pcSerialComUpdate()
{
    /*char receivedChar = pcSerialComCharRead();
    if( receivedChar != '\0' ) {
        switch ( pcSerialComMode ) {
            case PC_SERIAL_COMMANDS:
                pcSerialComCommandUpdate( receivedChar );
            break;

            case PC_SERIAL_GET_CODE:
                pcSerialComGetCodeUpdate( receivedChar );
            break;

            case PC_SERIAL_SAVE_NEW_CODE:
                pcSerialComSaveNewCodeUpdate( receivedChar );
            break;
            default:
                pcSerialComMode = PC_SERIAL_COMMANDS;
            break;
        }
    }//*/    
}

bool pcSerialComCodeCompleteRead()
{
    return codeComplete;
}

void pcSerialComCodeCompleteWrite( bool state )
{
    codeComplete = state;
}

//=====[Implementations of private functions]==================================

static void pcSerialComStringRead( char* str, int strLength )
{
    int strIndex;
    for ( strIndex = 0; strIndex < strLength; strIndex++) {
        uartUsb.read( &str[strIndex] , 1 );
        uartUsb.write( &str[strIndex] ,1 );
    }
    str[strLength]='\0';
}
