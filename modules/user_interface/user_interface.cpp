//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "siren.h"
#include "safe_car_system.h"
#include "display.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================


static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;
    matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    systemBlockedIndicatorUpdate();
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]==================================
static void userInterfaceDisplayInit()
{
    //displayInit(); idk what this is 
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Mode:" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Delay:" );
    
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    //char temperatureString[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        //sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
       // displayCharPositionWrite ( 12,0 );
        //displayStringWrite( temperatureString );
        //displayCharPositionWrite ( 14,0 );
        //displayStringWrite( "'C" );

        displayCharPositionWrite ( 5,0 );

        if ( WiperMode() == OFF_MODE ) 
            displayStringWrite( "OFF" );
        else if ( WiperMode() == INT_MODE ) {
            displayStringWrite( "INT" );
        else if ( WiperMode() == LOW_MODE ) {
            displayStringWrite( "LOW" );
        } else {
            displayStringWrite( "HIGH" );
        }

        displayCharPositionWrite ( 6,1 );
        
        if ( IntDelay() == SHORT_MODE ) {
            displayStringWrite( "SHORT " );
        else if ( IntDelay() == MEDIUM_MODE ) {
            displayStringWrite( "MEDIUM" );
        } else {
            displayStringWrite( "LONG" );
        }

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}