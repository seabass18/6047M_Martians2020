#include "vex.h"

using namespace vex;

vex::brain         Brain;
vex::motor         frontRight(PORT1, gearSetting::ratio18_1, true);
vex::motor         frontLeft(PORT2, gearSetting::ratio18_1);
vex::motor         backRight(PORT3, gearSetting::ratio18_1, true);
vex::motor         backLeft(PORT4, gearSetting::ratio18_1);
vex::motor         leftIntake(PORT6, gearSetting::ratio18_1);
vex::motor         rightIntake(PORT9, gearSetting::ratio18_1, true);
vex::motor         ramp(PORT7, true);
vex::motor         lift(PORT8);
vex::controller    Controller1; 
inertial           I(PORT11);
int Switch = 0;

void move(int deg, float seco){
  float x = sin(deg)*100;
  float y = cos(deg)*100;
  Controller1.Screen.print(x);
  Controller1.Screen.print("  ");
  Controller1.Screen.print(y);
  frontLeft.spin(fwd, y+x, velocityUnits::pct);
  frontRight.spin(fwd, y-x, velocityUnits::pct);
  backLeft.spin(fwd, y-x, velocityUnits::pct);
  backRight.spin(fwd, y+x, velocityUnits::pct);
  wait(seco, sec);
}

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

void strafeRight(float revs, int velo){

frontRight.startRotateFor(-revs, rotationUnits::rev, velo, velocityUnits::pct);
frontLeft.startRotateFor(revs, rotationUnits::rev, velo, velocityUnits::pct);
backRight.startRotateFor(revs, rotationUnits::rev, velo, velocityUnits::pct);
backLeft.rotateFor(-revs, rotationUnits::rev, velo, velocityUnits::pct);

}

void strafeLeft(float revs, int velo){

frontRight.startRotateFor(revs, rotationUnits::rev, velo, velocityUnits::pct);
frontLeft.startRotateFor(-revs, rotationUnits::rev, velo, velocityUnits::pct);
backRight.startRotateFor(-revs, rotationUnits::rev, velo, velocityUnits::pct);
backLeft.rotateFor(revs, rotationUnits::rev, velo, velocityUnits::pct);

}

void stacko(){

ramp.rotateFor( 2.5, rotationUnits::rev, 50, velocityUnits::pct );
ramp.rotateFor( 4, rotationUnits::rev, 20, velocityUnits::pct );

}

void GL(int deg){
  backLeft.setStopping(brakeType::brake);
  frontLeft.setStopping(brakeType::brake);
  backRight.setStopping(brakeType::brake);
  frontRight.setStopping(brakeType::brake);
  I.setRotation(0, rotationUnits::deg);
  while(I.rotation() > 360-deg){
    int turn = I.rotation()-360-deg;
    int driveVelocity=-(1/162)*turn*turn+25;
    frontLeft.spin(reverse, driveVelocity, velocityUnits::pct);
    frontRight.spin(forward, driveVelocity, velocityUnits::pct);
    backLeft.spin(reverse, driveVelocity, velocityUnits::pct);
    backRight.spin(forward, driveVelocity, velocityUnits::pct);
  }
  frontLeft.stop();
  frontRight.stop();
  backLeft.stop();
  backRight.stop();
}

void GR(int deg){
  backLeft.setStopping(brakeType::brake);
  frontLeft.setStopping(brakeType::brake);
  backRight.setStopping(brakeType::brake);
  frontRight.setStopping(brakeType::brake);
  I.setRotation(0, rotationUnits::deg);
  while(I.rotation() < deg){
    int turn = I.rotation();
    int driveVelocity=-(1/162)*turn*turn+25;
    frontLeft.spin(forward, driveVelocity, velocityUnits::pct);
    frontRight.spin(reverse, driveVelocity, velocityUnits::pct);
    backLeft.spin(forward, driveVelocity, velocityUnits::pct);
    backRight.spin(reverse, driveVelocity, velocityUnits::pct);
  }
  while(I.rotation() > deg){
    int driveVelocity = -5;
    frontLeft.spin(forward, driveVelocity, velocityUnits::pct);
    frontRight.spin(reverse, driveVelocity, velocityUnits::pct);
    backLeft.spin(forward, driveVelocity, velocityUnits::pct);
    backRight.spin(reverse, driveVelocity, velocityUnits::pct);
  }
  while(I.rotation() < deg){
    int driveVelocity = 1;
    frontLeft.spin(forward, driveVelocity, velocityUnits::pct);
    frontRight.spin(reverse, driveVelocity, velocityUnits::pct);
    backLeft.spin(forward, driveVelocity, velocityUnits::pct);
    backRight.spin(reverse, driveVelocity, velocityUnits::pct);
  }
  frontLeft.stop();
  frontRight.stop();
  backLeft.stop();
  backRight.stop();
}
