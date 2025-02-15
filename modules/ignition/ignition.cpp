// This program simulates an enhanced vehicle alarm system with various safety
// features. It uses input signals to detect driver and passenger presence,
// seatbelt fastening, and ignition button presses, and outputs status via LEDs
// and UART messages.
//**CHANGE DESCRIPTION**

//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"
#include <string>
#include "ignition.h"
#include "siren.h"
#include "pc_serial_com.h"


//=====[Defines]===============================================================

//uart macros
//#define UART_INTRO_KEY 0
//#define UART_ENGINE_KEY 1
//#define UART_ERROR_KEY 2


//=====[Declaration and initialization of public global objects]===============

DigitalIn driverPresent(D14);
DigitalIn passengerPresent(D15);
DigitalIn driverSeatbelt(D13);
DigitalIn passengerSeatbelt(D12);
DigitalIn ignitionButton(BUTTON1);
AnalogIn wiperModeSelector(A0);
AnalogIn wiperDelaySelector(A1);

DigitalOut greenIndicator(LED1);
DigitalOut blueIndicator(LED2);




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


//=====[Implementations of public functions]===================================

void inputsInit() {
  driverPresent.mode(PullDown);
  passengerPresent.mode(PullDown);
  driverSeatbelt.mode(PullDown);
  passengerSeatbelt.mode(PullDown);
  ignitionButton.mode(PullDown);
}

bool getDriverPresent(){
    return driverPresent;
}
bool getPassengerPresent(){
    return passengerPresent;
}
bool getDriverSeatbelt(){
    return driverSeatbelt;
}
bool getPassengerSeatbelt(){
    return passengerSeatbelt;
}


void outputsInit() {
  //**sirenPin.mode(OpenDrain);
  //**sirenPin.input();

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
        sirenOFF();
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
        sirenON();
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

