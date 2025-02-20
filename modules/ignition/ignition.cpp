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
#define UART_INTRO_KEY 0
#define UART_ENGINE_KEY 1
#define UART_ERROR_KEY 2


//=====[Declaration and initialization of public global objects]===============

DigitalIn driverPresent(D14);
DigitalIn passengerPresent(D15);
DigitalIn driverSeatbelt(D10);
DigitalIn passengerSeatbelt(D11);
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

int buttonReleaseTime = 0;
bool ignitionReleased = false;
bool engineRunning = OFF;
//bool blueIndicator ;
//bool greenIndicator = OFF;
 


ignitionState_t ignition_State = BUTTON_OFF_0;

// variables used in tracking the falling edge of the ignition button
bool ignitionPrevious = ON;
bool waitForRelease = false;

//=====[Declarations (prototypes) of public functions]=========================

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

/*
void ignitionState() {
  if (ignitionButton && !ignitionPrevious) {
    if (waitForRelease) {
      ignitionButtonState = !ignitionButtonState;
      waitForRelease = false;
    }
  }
  if (!ignitionButton && ignitionPrevious) {
    waitForRelease = true;
  }
  ignitionPrevious = ignitionButton;
} */

/*
activates when the ignition button is pressed and acts based on a case-to-case
basis Ex. uart messages are printed based on which buttons are not pressed to
start the engine if all buttons are pressed the engine will start
*/







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
  if (driverPresent && passengerPresent && driverSeatbelt && passengerSeatbelt) {
    greenIndicator = ON; // All conditions met, safe state
  } else {
    greenIndicator = OFF; // One or more conditions not met, unsafe state
  }
}

bool getEngineState() {
    return engineRunning;
}


bool isignitionon() {
    if (blueIndicator == ON){
    return true;
    }else {
    return false;
    }
}




void ignitionUpdate()
{
    
    switch (ignition_State) {
    case BUTTON_OFF_0:
    if (ignitionReleased) {
            sirenOFF();
            blueIndicator = OFF;
            greenIndicator = OFF;
            engineRunning = OFF;
    }
            if ( driverPresent ) {
                if (!introComplete) {
                    driverIntroduction();
                }
                }
                if (ignitionButton) {
                ignition_State = BUTTON_ON_1;
                }
            break;

    case BUTTON_ON_1:
            if ( driverPresent && passengerPresent && driverSeatbelt && passengerSeatbelt) {
                greenIndicator = ON;
                sirenOFF();}
            if(ignitionButton) {
                if(greenIndicator) {
                    ignition_State = BUTTON_READY_STATE;
                }
                else {
                    if (!blueIndicator && !ignitionReleased) {
                    sirenON();
                    uartCommands(UART_ERROR_KEY);
                    }
                }
            }
            break;

    case BUTTON_READY_STATE:
            sirenOFF();
            uartCommands(UART_ENGINE_KEY);
            blueIndicator = ON;
            greenIndicator = OFF;
            engineRunning = ON;
            //bool ignitionButttonRelease = false;
            if(!ignitionButton) {
                ignition_State = BUTTON_ON_2;
            }

            break;
    
    case BUTTON_ON_2:
            if (engineRunning) {
            ignitionReleased = false;
            }
            if (buttonReleaseTime < 1){
                delay(10);
                if (!ignitionButton) {
                    buttonReleaseTime ++;

                }
            }
            if (buttonReleaseTime >= 1 && ignitionButton){
                ignitionReleased = true;
                ignition_State = BUTTON_OFF_0;
            }
            break;

        }
    }


