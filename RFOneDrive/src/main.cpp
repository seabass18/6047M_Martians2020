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



int Stack(){
  while(1){

    double rampPosition=ramp.rotation(rev);
    double rampVelocity=-2.16*rampPosition*rampPosition+120;
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
  vex::task::sleep(50);
  lift.startRotateTo(2.05, rotationUnits::rev, 80, velocityUnits::pct);
}

void lowTower(){

  vex::task::sleep(50);
  lift.rotateTo(1.6, rotationUnits::rev, 100, velocityUnits::pct);

}

void resetArm(){

  ramp.startRotateTo(0, rotationUnits::rev, 100, velocityUnits::pct);
  wait(50, msec);
  lift.startRotateTo(0, rotationUnits::rev, 100, velocityUnits::pct);

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
/*intake(0);
forwards(2.3,30);
intake(0);
*/
/*

move();
*/
popRamp();
intakeSwitch(0, 100);
forwards(2.9, 40);
vexDelay(100);
strafeLeft(1, 50);
forwards(.8, 30);
vexDelay(400);
backward(1.5, 50);
intakeSwitch(0, 100);
backward(1.6, 60);
righto(1.4, 30);
move(90, .7);
vexDelay(100);
forwards(1.7, 40);
intakeSwitch(0,100);
vexDelay(300);
intakeSwitch(0, 100);
stacko();
vexDelay(200);
backward(2,50);

/*intakeSwitch(0, 100);
forwards(2, 40);
backward(1.65, 70);
vexDelay(100);
strafeRight(2.3, 60);
forwards(2.85, 40);
vexDelay(100);
backward(2.65, 80);
righto(1.4, 30);
intakeSwitch( 0, 100 );
move(90, .6);
vexDelay(100);
forwards(.6, 30);
stacko();
backward(2,50);*/


/*
forwards();
stack();

*/
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
  //task b(Debug);

/*Controller1.Screen.clearScreen();
Controller1.Screen.print("FR " && frontRight.temperature(temperatureUnits::fahrenheit));
Controller1.Screen.newLine();
Controller1.Screen.print("FL " && frontLeft.temperature(temperatureUnits::fahrenheit));
Controller1.Screen.newLine();
Controller1.Screen.print("BR " && backRight.temperature(temperatureUnits::fahrenheit));
Controller1.Screen.newLine();
Controller1.Screen.print("BL " && backLeft.temperature(temperatureUnits::fahrenheit));*/

  while (1) {
    frontLeft.spin(fwd, Controller1.Axis3.value()+Controller1.Axis4.value()+Controller1.Axis1.value()/2, velocityUnits::pct);
    frontRight.spin(fwd, Controller1.Axis3.value()-Controller1.Axis4.value()-Controller1.Axis1.value()/2, velocityUnits::pct);
    backLeft.spin(fwd, Controller1.Axis3.value()-Controller1.Axis4.value()+Controller1.Axis1.value()/2, velocityUnits::pct);
    backRight.spin(fwd, Controller1.Axis3.value()+Controller1.Axis4.value()-Controller1.Axis1.value()/2, velocityUnits::pct);

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
//bool isRampSpinning;
 //=false;


/* if (Controller1.ButtonY.pressing()){
   //Ramp Forward
   ramp.setVelocity(rampVelocity, pct);
   ramp.spin(fwd); 
   isRampSpinning=true;
 
 }
 else if (Controller1.ButtonB.pressing()){
   //Ramp Back
   ramp.spin(reverse, 100, pct);
   isRampSpinning=true;
 }

 else{
   //Keep Ramp in Position
   if (isRampSpinning==true){
   ramp.stop(brakeType::brake);
   isRampSpinning=false;
      }
    }
  }*/
 
/*---------------------------------------------------------------------------------End of Ramp Control---------------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------------Intake Controls---------------------------------------------------------------------------------*/
 //intakeState=NEUTRAL;
 
 if (Controller1.ButtonR1.pressing()){

   rightIntake.spin(fwd, 100, pct);
   leftIntake.spin(fwd, 100, pct);
   //intakeState=SPIN;
 
 }
 else if (Controller1.ButtonR2.pressing()){


   rightIntake.spin(reverse, 100, pct);
   leftIntake.spin(reverse, 100, pct);
   //intakeState=SPIN;
 
 }

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
  //Controller1.ButtonUp.pressed(highTower);
  Controller1.ButtonUp.pressed(highTower);
  Controller1.ButtonDown.pressed(lowTower);
  Controller1.ButtonLeft.pressed(resetArm);
  


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