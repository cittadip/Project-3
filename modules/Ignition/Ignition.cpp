// This program simulates an enhanced vehicle alarm system with various safety
// features. It uses input signals to detect driver and passenger presence,
// seatbelt fastening, and ignition button presses, and outputs status via LEDs
// and UART messages.
//**CHANGE DESCRIPTION**

//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include <string>


//=====[Defines]===============================================================

//uart macros
#define UART_INTRO_KEY 0
#define UART_ENGINE_KEY 1
#define UART_ERROR_KEY 2


//=====[Declaration and initialization of public global objects]===============

DigitalIn driverPresent(D14);
DigitalIn passengerPresent(D15);
DigitalIn driverSeatbelt(D13);
DigitalIn passengerSeatbelt(D12);
DigitalIn ignitionButton(BUTTON1);
AnalogIn wiperModeSelector(A0);
AnalogIn wiperDelaySelector(A1);

DigitalOut greenIndicator(LED1);
DigitalInOut sirenPin(PE_10);
DigitalOut blueIndicator(LED2);


UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
// UART interface for communication with a computer or external device
// USBTX and USBRX represent transmit and receive pins, respectively
// 115200 is the baud rate for serial communication

//=====[Declaration and initialization of public global variables]=============

int introComplete = false; // Tracks whether the welcome message for the driver
                           // has been displayed
bool ignitionButtonState = OFF; //******* try ON first (but also change the vals
                                //in ignitionCase to not be "!")

float potentiometerReading = 0.0;
float potentiometerReadingScaled = 0.0;

float lightReading = 0.0;

// variables used in tracking the falling edge of the ignition button
bool ignitionPrevious = ON;
bool waitForRelease = false;

//=====[Declarations (prototypes) of public functions]=========================

void drivingState();
void uartCommands(int cmd); 

//=====[Implementations of public functions]===================================

void inputsInit() {
  driverPresent.mode(PullDown);
  passengerPresent.mode(PullDown);
  driverSeatbelt.mode(PullDown);
  passengerSeatbelt.mode(PullDown);
  ignitionButton.mode(PullDown);
}

void outputsInit() {
  sirenPin.mode(OpenDrain);
  sirenPin.input();

  blueIndicator = OFF;  // Blue LED: Indicates engine running
  greenIndicator = OFF; // Green LED: Indicates safe state for operation
}

/*
Tracks the falling edge of the ignition button
Allows for the ignition button to turn the engine off on release
*/
void ignitionState() {
  if (!ignitionButton && ignitionPrevious) {
    if (!waitForRelease) {
      ignitionButtonState = !ignitionButtonState;
      waitForRelease = true;
    }
  }
  if (ignitionButton && !ignitionPrevious) {
    waitForRelease = false;
  }
  ignitionPrevious = ignitionButton;
}

/*
activates when the ignition button is pressed and acts based on a case-to-case
basis Ex. uart messages are printed based on which buttons are not pressed to
start the engine if all buttons are pressed the engine will start
*/
void ignitionCase() {
  // maybe change the if statement to look for a button release
  ignitionState();
  if (!ignitionButtonState) {
    // Check if all required conditions are met for engine start
    if (driverPresent && passengerPresent && driverSeatbelt &&
        passengerSeatbelt) {
      uartCommands(UART_ENGINE_KEY);

      // this loop does 1 loop of all the functions that would occur if when the
      // engine is on before checking if the button was pushes and released
      // again
      do {
        // Turn off the green indicator and activate the blue indicator
        greenIndicator = OFF;
        //  keep on blue led
        blueIndicator = ON;
        sirenPin.input();
        //  also check for headlights settings here
        ignitionState();
        // headlightState();
      } while (!ignitionButtonState);

      // if engine is off the headlights and blue indicator should be turned off
      blueIndicator = OFF;
    //   headlightOff();
    } else {
      // Display ignition failure message and reasons via UART
      // Report individual reasons for failure
      uartCommands(UART_ERROR_KEY);

      // The alarm will keep sounding until the engine is properly
      // started eg. passenger/driver present and seatbelts on
      do {
        sirenPin.output();
        sirenPin = LOW; // Activate siren signal
        drivingState();
      } while (!(driverPresent && passengerPresent && driverSeatbelt &&
                 passengerSeatbelt));
    }
  }
}

/*
prints the introduction string in uart when the driver detected for the first
time
*/
void driverIntroduction() {
  if (driverPresent && !introComplete) {
    uartCommands(UART_INTRO_KEY);
    introComplete = true;
  }
}

/*
a list of UART serial prints depending on the situation the car is in
@param cmd the uart that is selected to be printed
*/
void uartCommands(int cmd) {
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

    if (!driverPresent) {
      uartUsb.write("\nDriver not present.", 20);
    }
    if (!passengerPresent) {
      uartUsb.write("\nPassenger not present.", 23);
    }
    if (!driverSeatbelt) {
      uartUsb.write("\nDriver Seatbelt not fastened.", 30);
    }
    if (!passengerSeatbelt) {
      uartUsb.write("\nPassenger Seatbelt not fastened.", 33);
    }
    break;
  }
}

/*
tells the program what state the code is in; if green led should be on/off
and/or ignition pressed

The green indicator lights up when all safety conditions (driver and
passenger present, seatbelts fastened) are met, indicating that the vehicle
is in a safe state to operate.
*/
void drivingState() {
  driverIntroduction();
  if (driverPresent && passengerPresent && driverSeatbelt &&
      passengerSeatbelt) {
    greenIndicator = ON; // All conditions met, safe state
  } else {
    greenIndicator = OFF; // One or more conditions not met, unsafe state
  }
}

bool isignitionon() {
    if (blueIndicator == ON){
    return true;
    }else {
    return false;
    }
}

