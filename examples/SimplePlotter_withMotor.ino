/*
* LINEAR KINEMATICS
*Download the STEPPER DRIVER library as you already have the A4988 and DRV8825 
*drive libraries available at: https://github.com/laurb9/StepperDriver
*Before using the example, make sure that the stepper motor library is installed.
*example by Leandro Lima / HeavyTech @2019
 */
#include "A4988.h"
#include "MultiDriver.h"
#include "SyncDriver.h"
#include <gcode.h>


#define NUMCOMMANDS 2
// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
//Number of steps to take 1 millimeter
#define STEPS_MM 80
// Target RPM for X axis motor
#define MOTOR_X_RPM 120
// Target RPM for Y axis motor
#define MOTOR_Y_RPM 120

// X motor
#define DIR_X 5
#define STEP_X 2

// Y motor
#define DIR_Y 6
#define STEP_Y 3

// ENABLE INTERCONNECTED WITH OTHER DRIVES...
#define ENA 8
// If microstepping is set externally, make sure this matches the selected mode
// 1=full step, 2=half step, 4 = 1/4, 8 = 1/8 and 16 = 1/6 Microsteps.
#define MICROSTEPS 16

// 2-wire basic config, microstepping is hardwired on the driver
// Other drivers can be mixed and matched but must be configured individually
A4988 stepperX(MOTOR_STEPS, DIR_X, STEP_X, ENA);
A4988 stepperY(MOTOR_STEPS, DIR_Y, STEP_Y, ENA);

// Pick one of the two controllers below
// each motor moves independently, trajectory is a hockey stick
 MultiDriver controller(stepperX, stepperY);
// OR
// synchronized move, trajectory is a straight line
//SyncDriver controller(stepperX, stepperY);
void homing();
void moviment();
void gotoLocation();
/*
G28 - HOMING
G0 - SET COORDINATES -> G0 X{n} Y{n}
*/

commandscallback commands[NUMCOMMANDS] = {{"G1",homing}, {"G0", moviment}}; 
gcode Commands(NUMCOMMANDS,commands);

double X;
double Y;
void setup() {
    /*
     * Set target motors RPM.
     */
    Commands.begin();
    stepperX.begin(MOTOR_X_RPM, MICROSTEPS);
    stepperY.begin(MOTOR_Y_RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next two lines
     stepperX.setEnableActiveState(LOW);
     stepperY.setEnableActiveState(LOW);
}

void loop() {
  Commands.available();
}
void homing()
{
  // code to home machine
}

void gotoLocation(double x,double y)
{
  int stepsx = (x - X)*STEPS_MM; // DISTANCE VARIATION X
  int stepsy = (y - Y)*STEPS_MM; // DISTANCE VARIATION Y
   stepperX.enable();// ENABLE MOTOR X
   stepperY.enable();
   controller.move(stepsx,stepsy); //SEND CURRENT STEPS FOR DRIVE
   X = x; // SET LAST POSITION
   Y = y;
   stepperX.disable();// DISABLE MOTOR Y
   stepperY.disable();
   Commands.comment("X:" + String(x) + "; Y:" +String(y)); // DEBUG SERIAL
   
}
// added paramenter x and y in function MOVIMENT > SET GOTO LOCATION;
void moviment(){ 
    double newXValue = X;
    double newYValue = Y;
    if(Commands.availableValue('X')) // ADDED parameter X in G0
      newXValue = Commands.GetValue('X');
    if(Commands.availableValue('Y'))// ADDED parameter Y in G0
      newYValue = Commands.GetValue('Y');

    gotoLocation(newXValue,newYValue);
    
}
