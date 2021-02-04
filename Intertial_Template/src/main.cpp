/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  This program will turn right 90 degrees using the         */
/*                  Inertial Sensor.                                          */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         1               
// RightMotor           motor         10              
// Inert_Sensor         inertial      11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>     // std::string, std::to_string

using namespace std;
using namespace vex;

void DriveForward(double);
void TurnRight(int, int);
void DisplayDiagnostics();
void InitInert();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  for(int side = 1; side <= 4; side++){
    DriveForward(1);
    DisplayDiagnostics();
    TurnRight(90.0, 7);
  }

}

void DriveForward(double time){
  LeftMotor.setVelocity(50, percent);
  RightMotor.setVelocity(50, percent);
  LeftMotor.spin(vex::reverse);
  RightMotor.spin(vex::reverse);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
  wait(.5, seconds);
}

void TurnRight(int setDegrees, int cycles){
  InitInert();

  // Turns the robot to the right
  LeftMotor.setVelocity(20, percent);
  RightMotor.setVelocity(20, percent);
  for(int cycle = 1; cycle < cycles; cycle++){
    if (Inert_Sensor.rotation(degrees) <= setDegrees){
      LeftMotor.spin(vex::forward);
      RightMotor.spin(reverse);
      waitUntil((Inert_Sensor.rotation(degrees) >= setDegrees));
      LeftMotor.stop();
      RightMotor.stop();
    }
    else if (Inert_Sensor.rotation(degrees) >= setDegrees){
      LeftMotor.spin(reverse);
      RightMotor.spin(vex::forward);
      waitUntil((Inert_Sensor.rotation(degrees) <= setDegrees));
      LeftMotor.stop();
      RightMotor.stop();
    }
    LeftMotor.setVelocity(15/(cycle * 2), percent);
    RightMotor.setVelocity(15/(cycle * 2), percent);
    wait(.5, seconds);
  }

  /*
  while((setDegrees - Inert_Sensor.rotation(degrees)) != 0){
    // nothing
  }
  */
}

void DisplayDiagnostics(){
  Brain.Screen.print("Heading: %d", (Inert_Sensor.heading(degrees)));
  Brain.Screen.print("\n");
  Brain.Screen.print("Rotation: ", Inert_Sensor.rotation(degrees));
  Brain.Screen.print("\n");
  Brain.Screen.print("Orientation: ", Inert_Sensor.orientation(yaw,degrees));
  Brain.Screen.print("\n");
}

void InitInert(){
  Inert_Sensor.calibrate();
  // waits for the Inertial Sensor to calibrate
  while (Inert_Sensor.isCalibrating()) {
    wait(100, msec);
  }
}