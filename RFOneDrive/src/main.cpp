/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "MotorSetup+Functions.h"

using namespace vex;
//test

int speed = 100;
int stack = 100;

int Debug(){
  while(1){
    Brain.Screen.print(stack);
    wait(1, sec);
    Brain.Screen.clearLine();
  }
  return(0);
}

int Stack(){
  while(1){
      double rampPosition=ramp.rotation(rev);
      double rampVelocity=-2.16*rampPosition*rampPosition+100;
          Brain.Screen.clearLine(1);
       Brain.Screen.setCursor(1, 0);
       Brain.Screen.print("hello %f %f", rampPosition, rampVelocity);
       Brain.Screen.render();
    while(Controller1.ButtonA.pressing()){
     ramp.spin(forward, stack, velocityUnits::pct);
      if(stack > 20){
        stack = stack-0.000000000000005;
      }
      wait(1, msec);
    }
    stack = 100;
    
     if (Controller1.ButtonX.pressing()){
      //Push Ramp Forward
      ramp.setVelocity(70, pct);
      ramp.spin(fwd);
      /*
      rampSpeed=rampSpeed-10;
      Controller1.Screen.print("rampSpeed");*/

    }else if (Controller1.ButtonY.pressing()){
      ramp.setVelocity(rampVelocity, pct);
      ramp.spin(fwd); 

    }else if (Controller1.ButtonB.pressing()){
      //Move Ramp Back
      ramp.spin(reverse, 100, pct);
 
    } else{
      ramp.stop();
    }
  }
  return(0);
}


void highTower(){
  //Controller1.Screen.clearScreen();
  //Controller1.Screen.print("Position High Tower");
  //ramp.startRotateTo(3.5, rotationUnits::rev, 100, velocityUnits::pct);
  vex::task::sleep(50);
  lift.startRotateTo(2.05, rotationUnits::rev, 80, velocityUnits::pct);
  //Controller1.Screen.clearScreen();
}

void lowTower(){
  //Controller1.Screen.clearScreen();
  //Controller1.Screen.print("Position Low Tower");
  //ramp.startRotateTo(3.5, rotationUnits::rev, 100, velocityUnits::pct);
  vex::task::sleep(50);
  lift.rotateTo(1.37, rotationUnits::rev, 100, velocityUnits::pct);
  //Controller1.Screen.clearScreen();
}

void resetArm(){
  //Controller1.Screen.clearScreen();
  //Controller1.Screen.print("Position Arm Reset");
  lift.startRotateTo(0, rotationUnits::rev, 100, velocityUnits::pct);
  vex::task::sleep(50);
  ramp.startRotateTo(0, rotationUnits::rev, 100, velocityUnits::pct);
  //Controller1.Screen.clearScreen();
}

/*void stackCubes(){
  intake(0);
  forwards(1, 20);
  ramp.rotateTo(3, rotationUnits::rev, 50, velocityUnits::pct);
  intake(0);
  ramp.startRotateTo(2, rotationUnits::rev, 50, velocityUnits::pct);
  vex::task::sleep(100);
  backward(1, 30);
}*/



// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
popRamp();
ramp.rotateTo( 0, rev, 100, velocityUnits::pct);
intakeSwitch(0,100);
forwards(2.7,45);
wait(.5,sec);
backward(1.7,45);
intakeSwitch(0,100);
intakeSwitch(0,5);
wait(.5,sec);
righto(1.1,20);
intakeSwitch(0,5);
//outake(.25);
forwards(1.15,40);
ramp.rotateFor(3,rev,100, velocityUnits::pct);
ramp.startRotateFor(2.3, rev, 50, velocityUnits::pct);
wait(2,sec);
backward(1,100);
resetArm();
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  /*enum motorState {
    BRAKE=0,
    NEUTRAL=1,
    SPIN=2
  };
  motorState intakeState=NEUTRAL;
  motorState rampState=NEUTRAL;
  motorState liftState=NEUTRAL;*/
  // User control code here, inside the loop
  task a(Stack);
  task b(Debug);
  while (1) {
    frontLeft.spin(fwd, Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value(), velocityUnits::pct);
    frontRight.spin(fwd, Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value(), velocityUnits::pct);
    backLeft.spin(fwd, Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value(), velocityUnits::pct);
    backRight.spin(fwd, Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value(), velocityUnits::pct);

/*---------------------------------------------------------------------------------Arm Control---------------------------------------------------------------------------------*/
 bool isLiftSpinning;
 //=false;

 

 if (Controller1.ButtonL1.pressing()){
   //Lift Arm
  lift.spin(fwd, 100, pct);
  isLiftSpinning=true;
 
 }
 else if (Controller1.ButtonL2.pressing()){
   //Lower Arm
   lift.spin(reverse, 100, pct);
   isLiftSpinning=true;
 }

 else{
   //Keep Arm in Position
   if (isLiftSpinning==true){
   lift.stop(brakeType::brake);
   isLiftSpinning=false;
   }
 }
/*---------------------------------------------------------------------------------End of Arm Control---------------------------------------------------------------------------------*/
 
/*---------------------------------------------------------------------------------Ramp Function---------------------------------------------------------------------------------*/

/*float rampRevs = 5.3;
int rampSpeed;

while( ramp.value(vex::rotationUnits::rev) < rampRevs){
*/


  

/*---------------------------------------------------------------------------------End of Ramp Function---------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------Ramp Control---------------------------------------------------------------------------------*/
 bool isRampSpinning;
 //=false;
 
float rampSpeed=100; 


 
/*---------------------------------------------------------------------------------End of Ramp Control---------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------Intake Controls---------------------------------------------------------------------------------*/
 //intakeState=NEUTRAL;
 
 if (Controller1.ButtonR1.pressing()){
//Intake
   rightIntake.spin(fwd, 100, pct);
   leftIntake.spin(fwd, 100, pct);
   //intakeState=SPIN;
 
 }
 else if (Controller1.ButtonR2.pressing()){
//Outake

   rightIntake.spin(reverse, 100, pct);
   leftIntake.spin(reverse, 100, pct);
   //intakeState=SPIN;
 
 }
 //else if (intakeState==SPIN){
   else {
   //Brake
   //brakeType::brake prevents the intake from coasting which could potentially let cubes fall out or accidently be intaken
   rightIntake.stop(brakeType::brake);
   leftIntake.stop(brakeType::brake);
   //intakeState=BRAKE;
   
 }


 /*else {
   intakeState=NEUTRAL;
 }*/
/*---------------------------------------------------------------------------------End of Intake Controls---------------------------------------------------------------------------------*/




    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    //Strafe
    /*
     frontLeft.spin( fwd, Controller1.Axis3.position(), percent);
     backLeft.spin( fwd, Controller1.Axis3.position(), percent);
     frontRight.spin( reverse, Controller1.Axis2.position(), percent);
     backRight.spin( reverse, Controller1.Axis2.position(), percent);
    //Drive
     frontRight.spin( fwd, Controller1.Axis1.position(),percent);
     backLeft.spin( fwd, Controller1.Axis4.position(), percent);
     backRight.spin( fwd, Controller1.Axis1.position(), percent);
     frontLeft.spin( fwd, Controller1.Axis4.position(), percent);
*/




    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  Controller1.ButtonUp.pressed(highTower);
  Controller1.ButtonDown.pressed(lowTower);
  Controller1.ButtonLeft.pressed(resetArm);
  //Controller1.ButtonA.pressed(stackCubes);


  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
