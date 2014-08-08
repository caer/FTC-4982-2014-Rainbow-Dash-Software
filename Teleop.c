#pragma config(Hubs, S1, HTMotor, HTServo, none, none)
#pragma config(Hubs, S2, HTMotor, none, none, none)
#pragma config(Hubs, S3, HTMotor, none, none, none)
#pragma config(Hubs, S4, HTMotor, none, none, none)
#pragma config(Motor, mtr_S1_C1_1, FR, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S1_C1_2, FL, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S2_C1_1, BR, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S2_C1_2, BL, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S3_C1_1, BOOMR, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S3_C1_2, BOOML, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S4_C1_1, GUARDIANROLLER, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S4_C1_2, FLAGRAISER, tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    AB,                   tServoStandard)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C2_6,    servo6,               tServoNone)
/*Pragmas must be declared before anything, including comments.***************/
/*Any files including this one should have pragmas identical to these.********/

//File: Teleop.c
//Project: E-03-Rainbow Dash
//Creation Date: Jan 21, 2014
//
//Author: Brandon Sanders <brandon@mechakana.com>
//
//File executed when the Teleop phase begins.
//
//Confirmed to work on:
//Lego Mindstorms NXT
//
///////////////////////////////////////////////////////////////////////////////
//Copyright (c) 2014 Brandon Sanders <brandon@mechakana.com>
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.
///////////////////////////////////////////////////////////////////////////////
//

//Include modules.
#include "pegasus.h"
#include "guardian.h"

//Function: initializeRobot////////////////////////////////////////////////////
//
//[initializeRobot] performs any tasks that your robot may need to do before
//                  the beginning of the autonomous segment of the robot game.
//
//[initializeRobot] will be left empty if no initialization code is
//                  required.
//
void initializeRobot()
{
	//Silence motors.
	motor[FR] = 0;
	motor[FL] = 0;
	motor[BR] = 0;
	motor[BL] = 0;
	motor[BOOMR] = 0;
	motor[BOOML] = 0;
	motor[GUARDIANROLLER] = 0;
	motor[FLAGRAISER] = 0;

	//Have motors stall.
	bFloatDuringInactiveMotorPWM = false;
}

//Task: main///////////////////////////////////////////////////////////////////
//
//The following is the main code for the tele-op robot operation.  Customize
//as appropriate for your specific robot.
//
//At the end of the tele-op period, the FMS will automatically halt execution of
//the program.
//
task main()
{
	//Initialize our robot.
	initializeRobot();

	//Wait for the autonomous phase to begin.
	waitForStart();

	//Start the modules.
	StartTask(pegasusListener);
	StartTask(guardianListener);

	//Enable joystick auto updating.
	enableUpJoystickAuto();

	//Loop infinitely until the tele-op phase ends.
	while (true)
		wait1Msec(500);
}
