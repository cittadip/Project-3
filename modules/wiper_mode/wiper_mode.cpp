#include "wiper_mode.h"
#include "arm_book_lib.h"
#include "mbed.h"
#include "servo.h"
#include "safe_car_system.h"


#define Q1_LIMIT 2.5
#define Q2_LIMIT 5
#define Q3_LIMIT 7.5
#define Q4_LIMIT 7.5

#define ONE_THIRED .3333
#define TWO_THIRED .6666


#define DELAY 1000

AnalogIn WiperModeKnob(A0);
AnalogIn INT_MODE_DELAY(A1);

int WiperMode() {
  int state;
  float reading = WiperModeKnob.read();
  float val = reading / 0.1;

  if (val <= Q1_LIMIT) {
    state = OFF_MODE;
  } else if (val < Q2_LIMIT && val >= Q1_LIMIT) {
    state = LOW_MODE;
  } else if (val > Q2_LIMIT && val <= Q3_LIMIT) {
    state = INT_MODE;
  } else {
    SERVO_HIGH_MODE();
    state = HIGH_MODE;
  }

  return state;
}

int IntDelay() {

  int state;
  float Intreading = INT_MODE_DELAY.read();
  float val2 = Intreading;

  if (val2 >= TWO_THIRED) {
    state = SHORT_DELAY;
  } else if (val2 < TWO_THIRED && val2 >= ONE_THIRED) {
    state = MEDIUM_DELAY;
  } else {
    state = LONG_DELAY;
  }

  return state;
}

void WiperModeState() {
  switch (WiperMode()) {
  case OFF_MODE:
    SERVO_OFF_MODE();
    break;
  case INT_MODE:
    SERVO_INT_MODE();
    break;
  case LOW_MODE:
    SERVO_LOW_MODE();
    break;
  case HIGH_MODE:
    SERVO_HIGH_MODE();
    break;
  }
}


void INT_State() {
  switch (IntDelay()) {
  case OFF_MODE:
    SHORT_MODE();
    break;
  case INT_MODE:
    MEDIUM_MODE();
    break;
  case LOW_MODE:
    LONG_MODE();
    break;
 
  }
}