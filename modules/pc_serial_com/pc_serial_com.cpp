//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"
#include "pc_serial_com.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//char codeSequenceFromPcSerialCom[CODE_NUMBER_OF_KEYS];

//=====[Declaration and initialization of private global variables]============

// static pcSerialComMode_t pcSerialComMode = PC_SERIAL_COMMANDS;
// static bool codeComplete = false;
// static int numberOfCodeChars = 0;

// //=====[Declarations (prototypes) of private functions]========================

// static void pcSerialComStringRead( char* str, int strLength );

// static void pcSerialComGetCodeUpdate( char receivedChar );
// static void pcSerialComSaveNewCodeUpdate( char receivedChar );

// static void pcSerialComCommandUpdate( char receivedChar );

// static void availableCommands();



// /*
// void pcSerialComInit();
// char pcSerialComCharRead();
// void pcSerialComStringWrite( const char* str );
// void pcSerialComUpdate();
// bool pcSerialComCodeCompleteRead();
// void pcSerialComCodeCompleteWrite( bool state );
// void uartCommands(int cmd)
// */

// //=====[Implementations of public functions]===================================
// void uartCommands(int cmd) {
//   switch (cmd) {
//   case UART_INTRO_KEY:
//     uartUsb.write("\nWelcome to enhanced alarm system model 218-W24", 46);
//     break;

//   case UART_ENGINE_KEY:
//     uartUsb.write("\nEngine started.", 15);
//     break;
//   case UART_ERROR_KEY:
//     uartUsb.write("\nIgnition inhibited", 19);
//     uartUsb.write("\nReasons:", 9);

//     if (!driverPresent) {
//       uartUsb.write("\nDriver not present.", 20);
//     }
//     if (!passengerPresent) {
//       uartUsb.write("\nPassenger not present.", 23);
//     }
//     if (!driverSeatbelt) {
//       uartUsb.write("\nDriver Seatbelt not fastened.", 30);
//     }
//     if (!passengerSeatbelt) {
//       uartUsb.write("\nPassenger Seatbelt not fastened.", 33);
//     }
//     break;
//   }
// }

// void pcSerialComInit()
// {
//     availableCommands();
// }

// char pcSerialComCharRead()
// {
//     char receivedChar = '\0';
//     if( uartUsb.readable() ) {
//         uartUsb.read( &receivedChar, 1 );
//     }
//     return receivedChar;
// }

// void pcSerialComStringWrite( const char* str )
// {
//     uartUsb.write( str, strlen(str) );
// }

// void pcSerialComUpdate()
// {
//     char receivedChar = pcSerialComCharRead();
//     if( receivedChar != '\0' ) {
//         switch ( pcSerialComMode ) {
//             case PC_SERIAL_COMMANDS:
//                 pcSerialComCommandUpdate( receivedChar );
//             break;

//             case PC_SERIAL_GET_CODE:
//                 pcSerialComGetCodeUpdate( receivedChar );
//             break;

//             case PC_SERIAL_SAVE_NEW_CODE:
//                 pcSerialComSaveNewCodeUpdate( receivedChar );
//             break;
//             default:
//                 pcSerialComMode = PC_SERIAL_COMMANDS;
//             break;
//         }
//     }    
// }

// bool pcSerialComCodeCompleteRead()
// {
//     return codeComplete;
// }

// void pcSerialComCodeCompleteWrite( bool state )
// {
//     codeComplete = state;
// }

// //=====[Implementations of private functions]==================================

// static void pcSerialComStringRead( char* str, int strLength )
// {
//     int strIndex;
//     for ( strIndex = 0; strIndex < strLength; strIndex++) {
//         uartUsb.read( &str[strIndex] , 1 );
//         uartUsb.write( &str[strIndex] ,1 );
//     }
//     str[strLength]='\0';
// }

// static void pcSerialComGetCodeUpdate( char receivedChar )
// {
//     codeSequenceFromPcSerialCom[numberOfCodeChars] = receivedChar;
//     pcSerialComStringWrite( "*" );
//     numberOfCodeChars++;
//    if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS ) {
//         pcSerialComMode = PC_SERIAL_COMMANDS;
//         codeComplete = true;
//         numberOfCodeChars = 0;
//     } 
// }

// static void pcSerialComSaveNewCodeUpdate( char receivedChar )
// {
//     static char newCodeSequence[CODE_NUMBER_OF_KEYS];

//     newCodeSequence[numberOfCodeChars] = receivedChar;
//     pcSerialComStringWrite( "*" );
//     numberOfCodeChars++;
//     if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS ) {
//         pcSerialComMode = PC_SERIAL_COMMANDS;
//         numberOfCodeChars = 0;
//         codeWrite( newCodeSequence );
//         pcSerialComStringWrite( "\r\nNew code configured\r\n\r\n" );
//     }
// }