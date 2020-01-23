/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                           6047M The Martians                               */
/*                       👽Official Martians Code👽                          */
/*                              2019-2020                                     */
/*                                MC1.0                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "MotorSetup+DriveControl.h"
using namespace vex;

// A global instance of competition
competition Competition;


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
 // Initializing Robot Configuration.

 // All activities that occur before the competition starts
 // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                              MartiansAuton                                */
/*                                 MA1.0                                     */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
/*---------------------------------------------------------------------------------Beginning of Auton---------------------------------------------------------------------------------*/

/*--------------------------------------------------Pop Ramp Out--------------------------------------------------*/
/*
Old Auton
forwards(1,100);
backward(.5,100);
outake(2);
ramp.rotateFor(2, sec, 100,rpm);
lift.rotateFor(fwd,3,sec);
wait(1,sec);
lift.startRotateFor(reverse,2,rev,100,rpm);
ramp.rotateFor(reverse,3,sec, 100, rpm);
*/
/*--------------------------------------------------NEW AUTON--------------------------------------------------*/
popRamp();
ramp.rotateTo( 0, rev, 100, velocityUnits::pct);
intake(0);
forwards(3,50);
wait(.5,sec);
backward(1.7,60);
righto(1.2,100);
intake(0);
//outake(.25);
forwards(.9,100);
ramp.rotateFor(3,rev,100, velocityUnits::pct);
ramp.startRotateFor(2.3, rev, 50, velocityUnits::pct);
wait(2,sec);
backward(1,100);

/*--------------------------------------------------Backup Auton--------------------------------------------------*/
//popRamp();
//forwards(2,100);
//backward(2,100);



/*--------------------------------------------------Test--------------------------------------------------*/
/*
forwards(1,100);
                          wait(3,sec);
forwardsWhile(1,100);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
                          wait(3,sec);
backward(1,100);
                          wait(3,sec);
backwardWhile(1,100);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
                          wait(3,sec);
rights(1,100);
                          wait(3,sec);
rightsWhile(1,100);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
                           wait(3,sec);
lefts(1,100);
                           wait(3,sec);
leftsWhile(1,100);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
                          wait(3,sec);
intake(2);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
                         wait(3,sec);
outake(3);
ramp.rotateTo(1, rev);
ramp.rotateTo(-1.25, rev);
*/
/*--------------------------------------------------Auton--------------------------------------------------*/
/*
forwards(0,100);
intake(0);
rights(0,0);
forwards(0,100);
outakeWhile(0);
ramp.rotateFor(fwd,0,rev);
forwards(0,100);
backward(4,100);
*/
}

/*---------------------------------------------------------------------------------End of Auton---------------------------------------------------------------------------------*/ 

 
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                             MartiansUserControl                           */
/*                                   MUC1.0                                  */
/*---------------------------------------------------------------------------*/
 
void usercontrol(void) {
 // User control code here, inside the loop
 while (1) {
/*---------------------------------------------------------------------------------Ramp Control---------------------------------------------------------------------------------*/
 if (Controller1.ButtonX.pressing()){
ramp.setVelocity(60,pct);
   ramp.spin(fwd);
 
 }
 else if (Controller1.ButtonY.pressing()){
ramp.setVelocity(30,pct);
   ramp.spin(fwd);
 
 }
 else if (Controller1.ButtonB.pressing()){
//Move Ramp Back
   ramp.spin(reverse,80,pct);
 
 }
 else {
//Stop Ramp From Falling After Moving Up
   ramp.stop(brakeType::brake);
 
 }
/*---------------------------------------------------------------------------------End of Ramp Control---------------------------------------------------------------------------------*/
 
 
 
/*---------------------------------------------------------------------------------Intake Controls---------------------------------------------------------------------------------*/
 if (Controller1.ButtonR1.pressing()){
//Intake
   rightIntake.spin(fwd, 100, pct);
   leftIntake.spin(fwd, 100, pct);
 
 }
 else if (Controller1.ButtonR2.pressing()){
//Outake

   rightIntake.spin(reverse, 100, pct);
   leftIntake.spin(reverse, 100, pct);
 
 }
 else{
   //Brake
   rightIntake.stop(brakeType::brake);
   leftIntake.stop(brakeType::brake);
   //brakeType::brake prevents the intake from coasting which could potentially let cubes fall out or accidently be intaken
 
 }
/*---------------------------------------------------------------------------------End of Intake Controls---------------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------------Arm Control---------------------------------------------------------------------------------*/
 if (Controller1.ButtonL1.pressing()){
   //Lift Intakes
lift.spin(fwd, 80, pct);
 
 }
 else if (Controller1.ButtonL2.pressing()){
   //Lower Intakes
   lift.spin(reverse, 80, pct);
 
 }

 else{
   //Keep Intakes in Position
   lift.stop(brakeType::brake);
 //brakeType::brake keeps the Intakes from moving upwards when a cube is being intaked
 }
/*---------------------------------------------------------------------------------End of Arm Control---------------------------------------------------------------------------------*/
 /*if (Controller1.ButtonLeft.pressing()){

//Small Tower
ramp.rotateFor(1,sec);
lift.rotateFor(1,rev);

 }

if(Controller1.ButtonRight.pressing()){

//Tall Tower
ramp.rotateFor(1,sec);
lift.rotateFor(1.5,rev);

}
*/


/*
if (Controller1.ButtonUp.pressing()){
frontLeft.setVelocity(100,pct);
backLeft.setVelocity(100,pct);
frontRight.setVelocity(100,pct);
backRight.setVelocity(100,pct);


}

if (Controller1.ButtonDown.pressing()){
frontLeft.setVelocity(50,pct);
backLeft.setVelocity(50,pct);
frontRight.setVelocity(50,pct);
backRight.setVelocity(50,pct);


}
*/
/*---------------------------------------------------------------------------------Joystick Control---------------------------------------------------------------------------------*/
     frontLeft.setVelocity(Controller1.Axis3.position(), percent);
     backLeft.setVelocity(Controller1.Axis3.position(), percent);
     frontRight.setVelocity(Controller1.Axis2.position(), percent);
     backRight.setVelocity(Controller1.Axis2.position(), percent);

frontLeft.spin(fwd);
backLeft.spin(fwd);
frontRight.spin(fwd);
backRight.spin(fwd);


/*---------------------------------------------------------------------------------End of Joystick Control---------------------------------------------------------------------------------*/
 
   wait(20, msec); // Sleep the task for a short amount of time to
                   // prevent wasted resources.
 }
}
 
//
// Main will set up the competition functions and callbacks.
//
int main() {
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