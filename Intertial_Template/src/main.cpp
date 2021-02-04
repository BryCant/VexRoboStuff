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
  InitInert();

  TurnRight(90, 3);
  float totalInertVal = (Inert_Sensor_12.heading(degrees) + Inert_Sensor_12.heading(degrees));
  cout << "Total: " << totalInertVal;
    
  float averageInertVal = totalInertVal/2;
  cout << "Average: " << averageInertVal;

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
  //set inert sensor headings to zero
  InitInert();

  // Turns the robot to the right
  LeftMotor.setVelocity(40, percent);
  RightMotor.setVelocity(40, percent);

  for(int cycle = 1; cycle < cycles; cycle++){
    float totalInertVal = (Inert_Sensor_12.heading(degrees) + Inert_Sensor_12.heading(degrees));
    cout << "Total: " << totalInertVal;
    
    float averageInertVal = totalInertVal/2;
    cout << "Average: " << averageInertVal;
    
    if (abs(averageInertVal - setDegrees) > .5){
        if (Inert_Sensor_11.rotation(degrees) <= setDegrees){
      LeftMotor.spin(vex::forward);
      RightMotor.spin(reverse);
      waitUntil((Inert_Sensor_11.rotation(degrees) >= setDegrees));
      LeftMotor.stop();
      RightMotor.stop();
    }
    else if (Inert_Sensor_11.rotation(degrees) >= setDegrees){
      LeftMotor.spin(reverse);
      RightMotor.spin(vex::forward);
      waitUntil((Inert_Sensor_11.rotation(degrees) <= setDegrees));
      LeftMotor.stop();
      RightMotor.stop();
    }
    LeftMotor.setVelocity(15/(cycle * 2), percent);
    RightMotor.setVelocity(15/(cycle * 2), percent);
    wait(1, seconds);
    }
    
  }

}

void DisplayDiagnostics(){
  //Brain.Screen.print();
  cout << "Heading11: " << Inert_Sensor_11.rotation(degrees);
  cout << ", Heading12: " << Inert_Sensor_12.rotation(degrees) << endl;
  Brain.Screen.print("\n");
  Brain.Screen.print("Rotation: ", Inert_Sensor_11.rotation(degrees));
  Brain.Screen.print("\n");
  Brain.Screen.print("Orientation: ", Inert_Sensor_11.orientation(yaw,degrees));
  Brain.Screen.print("\n");
}

void InitInert(){
  Inert_Sensor_11.calibrate();
  // waits for the Inertial Sensor to calibrate
  while (Inert_Sensor_11.isCalibrating()) {
    wait(100, msec);
  }
  Inert_Sensor_12.calibrate();
  // waits for the Inertial Sensor to calibrate
  while (Inert_Sensor_12.isCalibrating()) {
    wait(100, msec);
  }
}