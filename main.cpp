//=====[Libraries]=============================================================

#include "safe_car_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
   safeCarSystemInit();
    while (true) {
        safeCarSystemUpdate();
    }
}