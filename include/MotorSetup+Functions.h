#include "vex.h"

using namespace vex;

vex::motor         frontRight(PORT16, gearSetting::ratio18_1, true);
vex::motor         frontLeft(PORT2, gearSetting::ratio18_1);
vex::motor         backRight(PORT3, gearSetting::ratio18_1, true);
vex::motor         backLeft(PORT4, gearSetting::ratio18_1);
vex::motor         leftIntake(PORT7, gearSetting::ratio18_1);
vex::motor         rightIntake(PORT9, gearSetting::ratio18_1, true);
vex::motor         ramp(PORT5, true);
vex::motor         lift(PORT6, true);
vex::controller    Controller1;

int Switch = 0;
void forwards( float rotations, int vel ){

frontRight.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
frontLeft.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backRight.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backLeft.rotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
}

void forwardsWhile( float rotations, int vel ){

frontRight.startRotateTo(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
frontLeft.startRotateTo(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backRight.startRotateTo(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backLeft.startRotateTo(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
}

void backward( float rotations, int vel ){

frontRight.startRotateFor(-rotations,rev,vel,vex::velocityUnits::pct);
frontLeft.startRotateFor(-rotations,rev,vel,vex::velocityUnits::pct);
backRight.startRotateFor(-rotations,rev,vel,vex::velocityUnits::pct);
backLeft.rotateFor(-rotations,rev,vel,vex::velocityUnits::pct);
}

void righto( float rotations, int vel ){

frontRight.startRotateFor(-rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
frontLeft.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backRight.startRotateFor(-rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backLeft.rotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
}

void lefto(float rotations,int vel){

frontRight.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
frontLeft.startRotateFor(-rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backRight.startRotateFor(rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
backLeft.rotateFor(-rotations,rotationUnits::rev,vel,vex::velocityUnits::pct);
}


void intake(float Back){
rightIntake.setVelocity(100,pct);
leftIntake.setVelocity(100,pct);
if(Back != 0){
  rightIntake.startRotateFor(Back, rev);
  leftIntake.startRotateFor(Back, rev);
}else if(Switch == 0){
  rightIntake.spin(forward);
  leftIntake.spin(forward);
  Switch = 1;
} else{
  rightIntake.stop();
  leftIntake.stop();
  Switch = 0;
}

}

void outake(float distance){

rightIntake.startRotateFor(-distance,rev, 200,rpm);
leftIntake.startRotateFor(-distance,rev, 200,rpm);

}
