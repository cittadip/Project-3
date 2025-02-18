//=====[Libraries]=============================================================

#include "safe_car_system.h"
#include "user_interface.h"
#include "servo.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    safeCarSystemInit();
    while (true) {
        SERVO_HIGH_MODE();
        servo_update_function();
        safeCarSystemUpdate();
    }
}