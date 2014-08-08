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

//File: Guardian.h
//Project: E-03-Rainbow Dash
//Date: Jan 21, 2014
//
//Author: Brandon Sanders <brandon@mechakana.com>
//
//Confirmed to work on:
//Lego Mindstorms NXT
//
///////////////////////////////////////////////////////////////////////////////
//Copyright (c) 2014 Brandon Sanders <brandon@mechakana.com>
//
//All rights reserved.
///////////////////////////////////////////////////////////////////////////////
//
#ifndef GUARDIAN_H_
#define GUARDIAN_H_

//Modified joystick driver to allow easy software-based joystick swapping.
#include "upgradedJoystick.h"

//Global variables and definitions.
#include "definitions.h"

#ifndef CHECK_FUNCTION_F_
#define CHECK_FUNCTION_F_

//Function: check//////////////////////////////////////////////////////////////
//
//[check] checks if the passed value is above or below the jostick deadzones,
//        allowing us to tell whether or not we should respond to input.
//
bool check(int direction)
{
	if (direction > ERROR_TOP)
		return true;

	else if (direction < ERROR_BOTTOM)
		return true;

	return false;
}
#endif

//Function: canRaise///////////////////////////////////////////////////////////
//
//
//
bool canRaise()
{
	//Is the limit switch hit?
	//return SensorValue(TOUCHMUX) & MUX1;
	return true;
}

//Function: canLower///////////////////////////////////////////////////////////
//
//
//
bool canLower()
{
	//Is the limit switch hit?
	//return SensorValue(TOUCHMUX) & MUX2;
  return true;
}

//Function: guardianListener///////////////////////////////////////////////////
//
//I wonder, what do you THINK it does? ;D
//
task guardianListener()
{
	//Loop infinitely.
	while (true)
	{
		//Mandibles////////////////////////////////////////////////////////////
		//
		//Manage feeding/barfing action on the mandibles.
		//
		if (upJoy2Btn(5)) //Feed.
		{
			motor[GUARDIANROLLER] = 100;
		}

		else if (upJoy2Btn(6)) //Barf.
		{
			motor[GUARDIANROLLER] = -100;
		}

		else //Stop.
		{
			motor[GUARDIANROLLER] = 0;
		}

		//Boom/////////////////////////////////////////////////////////////////
		//
		//Manage up/down action on the boom.
		//check(upJoystick.joy2_y2) && upJoystick.joy2_y2 < 0 && canLower()
		if(check(upJoystick.joy2_y2) && upJoystick.joy2_y2 < 0 && canLower()) //Up.
		{
			motor[BOOMR] = BOOM_SPEED_UP;
			motor[BOOML] = BOOM_SPEED_UP;
		}

		else if(check(upJoystick.joy2_y2) && upJoystick.joy2_y2 > 0 && canRaise()) //Down.
		{
			motor[BOOMR] = BOOM_SPEED_DOWN;
			motor[BOOML] = BOOM_SPEED_DOWN;
		}

		else //Stop.
		{
			motor[BOOMR] = 0;
			motor[BOOML] = 0;
		}

		//Flag raiser.
		if (check(upJoystick.joy2_y1) && upJoystick.joy2_y1 > 0)
			motor[FLAGRAISER] = 100;

		else if (check(upJoystick.joy2_y1) && upJoystick.joy2_y1 < 0)
			motor[FLAGRAISER] = -100;

		else
			motor[FLAGRAISER] = 0;

		//Toggle software joystick flipping////////////////////////////////////////
		//
		//Press "BACK" to enable software joystick flipping.
		//Press "START" to disable software joystick flipping.
		//
		if (upJoy2Btn(9))
			flipJoystick(true);

		else if (upJoy2Btn(10))
			flipJoystick(false);

		//Allow the other processes time to do stuff.
		wait1Msec(100);
	}
}

#endif
