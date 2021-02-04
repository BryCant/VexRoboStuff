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
// Inert_Sensor_11      inertial      11              
// Inert_Sensor_12      inertial      12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>     // std::string, std::to_string
#include <cmath>
#include <iostream>

using namespace std;
using namespace vex;

void DriveForward(double);
void TurnRight(int, int);
void DisplayDiagnostics();
void InitInert();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  for(int side = 1; side <= 4; side++)
  {
    InitInert();
    DriveForward(1);
    TurnRight(90, 6);
  }
}

// -------------- FUNTIONS -------------- //

void DriveForward(double time){
  LeftMotor.setVelocity(25, percent);
  RightMotor.setVelocity(25, percent);
  LeftMotor.spin(vex::forward);
  RightMotor.spin(vex::forward);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
  wait(.5, seconds);
}

void TurnRight(int setDegrees, int cycles){
  // Turns the robot to the right
  LeftMotor.setVelocity(30, percent);
  RightMotor.setVelocity(30, percent);

  for(int cycle = 1; cycle < cycles; cycle++){
    // Gets average of inertial sensors
    float totalInertVal = (Inert_Sensor_12.heading(degrees) + Inert_Sensor_12.heading(degrees));
    float averageInertVal = totalInertVal/2;

    if (abs(averageInertVal - abs(setDegrees)) > .5)   //
    {
        if (Inert_Sensor_11.rotation(degrees) <= setDegrees){
        LeftMotor.spin(vex::reverse);
        RightMotor.spin(vex::forward);
        waitUntil((Inert_Sensor_11.rotation(degrees) >= setDegrees));
        LeftMotor.stop();
        RightMotor.stop();
        }
        else if (Inert_Sensor_11.rotation(degrees) >= setDegrees){
          LeftMotor.spin(vex::forward);
          RightMotor.spin(vex::reverse);
          waitUntil((Inert_Sensor_11.rotation(degrees) <= setDegrees));
          LeftMotor.stop();
          RightMotor.stop();
        }
      LeftMotor.setVelocity(5, percent);
      RightMotor.setVelocity(5, percent);
      wait(1, seconds);
    }
  }
  // Gets average of inertial sensors
  float totalInertVal = (Inert_Sensor_12.heading(degrees) + Inert_Sensor_12.heading(degrees));
  float averageInertVal = totalInertVal/2;

  Brain.Screen.print(abs(averageInertVal - abs(setDegrees)));
  Brain.Screen.print("|");
}

void InitInert(){
  Inert_Sensor_11.calibrate();
  Inert_Sensor_12.calibrate();
  // waits for the Inertial Sensor 11 to calibrate
  while (Inert_Sensor_11.isCalibrating() || Inert_Sensor_12.isCalibrating()) {
    wait(50, msec);
  }
}