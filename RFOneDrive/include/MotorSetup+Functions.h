#include "vex.h"

using namespace vex;

vex::brain         Brain;
vex::motor         frontRight(PORT1, gearSetting::ratio18_1, true);
vex::motor         frontLeft(PORT2, gearSetting::ratio18_1);
vex::motor         backRight(PORT3, gearSetting::ratio18_1, true);
vex::motor         backLeft(PORT4, gearSetting::ratio18_1);
vex::motor         leftIntake(PORT6, gearSetting::ratio18_1);
vex::motor         rightIntake(PORT5, gearSetting::ratio18_1, true);
vex::motor         ramp(PORT7, true);
vex::motor         lift(PORT8);
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


void intakeSwitch(float Back, int percent){

rightIntake.setVelocity(percent,pct);
leftIntake.setVelocity(percent,pct);
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

void intake(float distance){

rightIntake.startRotateFor(distance,rev, 200,rpm);
leftIntake.startRotateFor(distance,rev, 200,rpm);

}



void popRamp(){

intakeSwitch(0,100);
wait(500,msec);
ramp.startRotateTo(2.5, rotationUnits::rev, 100, velocityUnits::pct);
task::sleep(300);
lift.rotateTo(2, rotationUnits::rev, 100, velocityUnits::pct);
intakeSwitch(0,100);
lift.rotateTo(0, rotationUnits::rev, 100, velocityUnits::pct);

}