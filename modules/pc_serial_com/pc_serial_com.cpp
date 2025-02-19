//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "pc_serial_com.h"
#include "servo.h"

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
void writeAngle();


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
    availableCommands();
}

void uartCommands(int cmd) 
{
  switch (cmd) {
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
  }
}

static void availableCommands()
{
    pcSerialComStringWrite( "Available commands:\r\n" );
    pcSerialComStringWrite( "Press '1' to get the alarm state\r\n" );
    pcSerialComStringWrite( "Press '2' to get the gas detector state\r\n" );
    pcSerialComStringWrite( "Press '3' to get the over temperature detector state\r\n" );
    pcSerialComStringWrite( "Press '4' to enter the code to deactivate the alarm\r\n" );
    pcSerialComStringWrite( "Press '5' to enter a new code to deactivate the alarm\r\n" );
    pcSerialComStringWrite( "Press 'f' or 'F' to get lm35 reading in Fahrenheit\r\n" );
    pcSerialComStringWrite( "Press 'c' or 'C' to get lm35 reading in Celsius\r\n" );
    pcSerialComStringWrite( "Press 's' or 'S' to set the date and time\r\n" );
    pcSerialComStringWrite( "Press 't' or 'T' to get the date and time\r\n" );
    pcSerialComStringWrite( "Press 'e' or 'E' to get the stored events\r\n" );
    pcSerialComStringWrite( "\r\n" );
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
    char receivedChar = pcSerialComCharRead();
    // writeAngle();
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
    }   
}
/*
            sprintf ( str, "Temperature: %.2f \xB0 F\r\n", 
                celsiusToFahrenheit( 
                    analogReadingScaledWithTheLM35Formula (
                        potentiometer.read() ) ) );
            stringLength = strlen(str);
            uartUsb.write( str, stringLength );
*/
void writeAngle() {
    char str[100];
    int angle = getAngle();
    int stringLength;

    sprintf ( str, "%.2d\r\n", angle);
    stringLength = strlen(str);
    uartUsb.write( str, stringLength );

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
