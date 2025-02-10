//=====[Libraries]=============================================================

#include "Safe_Car_System.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
   SafeCarSystemInit();
    while (true) {
        SafeCarSystemUpdate();
    }
}