#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT1, ratio18_1, true);
motor RightMotor = motor(PORT10, ratio18_1, false);
inertial Inert_Sensor_11 = inertial(PORT11);
inertial Inert_Sensor_12 = inertial(PORT12);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}