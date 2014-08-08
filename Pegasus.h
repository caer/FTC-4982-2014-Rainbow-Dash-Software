#pragma config(Hubs, S1, HTMotor, HTServo, none, none)
#pragma config(Hubs, S2, HTMotor, none, none, none)
#pragma config(Hubs, S3, HTMotor, none, none, none)
#pragma config(Hubs, S4, HTMotor, none, none, none)
#pragma config(Motor, mtr_S1_C1_1, FR, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S1_C1_2, FL, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S2_C1_1, BR, tmotorTetrix, openLoop, reversed)
#pragma config(Motor, mtr_S2_C1_2, BL, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S3_C1_1, LIFTR, tmotorTetrix, openLoop)
#pragma config(Motor, mtr_S3_C1_2, LIFTL, tmotorTetrix, openLoop, reversed)
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

//File: pegasus.h
//Project: E-03-Rainbow Dash
//Creation Date: Jan 21, 2014
//
//Author: Brandon Sanders <brandon@mechakana.com>
//
//Yes, we really did use holonomic drivetrain code for the west coast drivetrain
//due to a lack of time...
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
#ifndef PEGASUS_H_
#define PEGASUS_H_

//Modified joystick driver to allow easy software-based joystick swapping.
#include "upgradedJoystick.h"

//Global variables and definitions.
#include "definitions.h"

//Variables////////////////////////////////////////////////////////////////////

//Is Low Sensitivity (Slow) mode turned on?
bool slow = false;

//Functions////////////////////////////////////////////////////////////////////
bool check(int direction);

float limit(float num);

float getMagnitude(float x, float y);

float getDirectionDegrees(float x, float y);

//Function: setMotor///////////////////////////////////////////////////////////
//
//[setMotor] sets the passed motor to the passed value.  It was originally
//           created so that other operations could be performed on motors 
//           before they were set, like ramping, but remained unused as the 
//           season progressed.
//
void setMotor(tMotor newMotor, float speed, int motorIndex)
{
	if (speed == 0)
	{
		if (motor[newMotor] > 0)
			motor[newMotor] = 0; //1;

		else if (motor[newMotor] < 0)
			motor[newMotor] = 0; //-1;
	}

	else
		motor[newMotor] = speed * 100;
}

//Function: check//////////////////////////////////////////////////////////////
//
//[check] checks if the passed value is above or below the jostick deadzones,
//        allowing us to tell whether or not we should respond to input.
//
#ifndef CHECK_FUNCTION_F_
#define CHECK_FUNCTION_F_
bool check(int direction)
{
	if (direction > ERROR_TOP || direction < ERROR_BOTTOM)
		return true;

	return false;
}
#endif

//Function: limit//////////////////////////////////////////////////////////////
//
//Returns a scaled back version of the passed value IF it exceeds the positive
//and negative thresholds of our number system.
//
float limit(float num)
{
	if (num > 1.0)
		return 1.0;

	else if (num < -1.0)
		return -1.0;

	return num;
}

//Function: getMagnitude///////////////////////////////////////////////////////
//
//Returns an average magnitude based on an X and Y axis value.
//
float getMagnitude(float x, float y)
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

//Function: getDirectionDegrees////////////////////////////////////////////////
//
//Returns a direction in degrees based on an X and Y axis value.
//
float getDirectionDegrees(float x, float y)
{
	return (180 / acos(-1)) * atan2(x, y);
}

//Function: holonomicDrive/////////////////////////////////////////////////////
//
//Using sine, cosine and another amazing mathematical formulae that nobody
//should even bother understanding, you too can have a holonomic drivetrain
//for practically free!
//
void holonomicDrive(float magnitude, float direction, float rotation)
{
		//Normalized for full power along the Cartesian axes.
		magnitude = limit(magnitude) * sqrt(2.0);

		//The rollers are at 45 degree angles.
		float dirInRad = (direction + 45.0) * 3.14159 / 180.0;
		float cosD = cos(dirInRad);
		float sinD = sin(dirInRad);

		//Calculate trajectory.
		float fl = sinD * magnitude + rotation; //sinD * magnitude + rotation;
		float fr = cosD * magnitude - rotation;
		float bl = cosD * magnitude + rotation;
		float br = sinD * magnitude - rotation; //sinD * magnitude - rotation;

		//Set motors.
		setMotor(FR, fr, 1);
		setMotor(FL, fl, 2);
		setMotor(BR, br, 3);
		setMotor(BL, bl, 4);

		//Convert to proper decimal place.  TODO: Pointless now...
		fl = fl * 100;
		fr = fr * 100;
		bl = bl * 100;
		br = br * 100;
}

//Function: pegasusListener////////////////////////////////////////////////////
//
//[pegasusListener] handles control of the Pegasus drivetrain.  Uses software
//from holonomic drivetrains to allow for better turning.
//
task pegasusListener()
{
	while (true)
	{
		//Drive////////////////////////////////////////////////////////////////////

		//Read in the Joystick values.
		float xRaw = (upJoystick.joy1_x1); //*0.8
		float yRaw = (upJoystick.joy1_y1);
		float zRaw = (upJoystick.joy1_x2);

		//TODO: Y = 0 always
		xRaw = 0.0;

		//Scale the joystick values down if slow mode is turned on.
		if (slow)
		{
			xRaw = xRaw * 0.15;
			yRaw = yRaw * 0.15;
			zRaw = zRaw * 0.35;
		}

		//Check the joystick values.
		if (!check(xRaw))
			xRaw = 0;
		if (!check(yRaw))
			yRaw = 0;
		if (!check(zRaw))
			zRaw = 0;

		//Scale back joystick values.
		if (xRaw > 100)
			xRaw = 100;
		if (yRaw > 100)
			yRaw = 100;
		if (zRaw > 100)
			zRaw = 100;
		if (xRaw < -100)
			xRaw = -100;
		if (yRaw < -100)
			yRaw = -100;
		if (zRaw < -100)
			zRaw = -100;

		//Convert the joystick values to a -1.0 to 1.0 system.
		xRaw = xRaw * 0.01;
		yRaw = yRaw * 0.01;
		zRaw = zRaw * 0.01;

		//Send the joystick values to the drive manager.
		holonomicDrive(getMagnitude(xRaw, yRaw), getDirectionDegrees(xRaw, yRaw), zRaw);

		//Toggle slow mode///////////////////////////////////////////////////////////
		//
		//Press the Right Bumper to turn off slow mode.
		//Press the Left Bumper to turn on slow mode.
		//
		if (upJoy1Btn(3))
			slow = true;
		else if (upJoy1Btn(1))
			slow = false;

		//Toggle software joystick flipping////////////////////////////////////////
		//
		//Press "BACK" to enable software joystick flipping.
		//Press "START" to disable software joystick flipping.
		//
		if (upJoy1Btn(9))
			flipJoystick(true);

		else if (upJoy1Btn(10))
			flipJoystick(false);

		//Allow the other processes time to do stuff.
		wait1Msec(50);
	}
}

#endif
