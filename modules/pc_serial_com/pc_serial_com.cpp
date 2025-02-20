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

void uartCommands(int cmd);
// void writeAngle();


//=====[Implementations of public functions ===================================

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
// UART interface for communication with a computer or external device
// USBTX and USBRX represent transmit and receive pins, respectively
// 115200 is the baud rate for serial communication


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
