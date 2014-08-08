//File: upgradedJoystick.h
//Project: Upgraded Joystick Driver
//Creation Date: Nov 20, 2012
//Last Update: Aug 8, 2014
//
//This file contains a set of overlays designed to supplement the standard
//JoystickDriver API as a drop-in replacement to the JoystickDriver.c file.
//
//The only differences between upgradedJoystick and JoystickDriver are:
//
// 1. Joystick flipping.  This allows joystick 1 to become joystick 2, and
//    vice versa.
//
// 2. Automatic background multithreading.
//
//As upgradedJoystick relies on a pre-existing JoystickDriver file, it should
//remain functional across any version of RobotC.
//
//Be advised: the following functions and variables need to be renamed if you
//            were previously using JoystickDriver.c:
//
//            joy1Btn(); becomes upJoy1Btn();
//            joy2Btn(); becomes upJoy2Btn();
//            getJoystickSettings(joystick); becomes getUpJoystick();
//            joystick.XYZ becomes upJoystick.XYZ
//
//By default, including this file will automatically start the upgraded joystick
//background task; this eliminates the need for any and all [getUpJoystick] in
//your program.
//
//If you wish to disable automatic joystick updating and instead use the manual
//[getUpJoystick] method, call the [disableUpJoystickAuto] function.  To
//re-enable auto updating, call the [enableUpJoystickAuto] function.
//
//Author: Brandon Sanders <brandon@mechakana.com>
//
//Confirmed to work on:
//Lego Mindstorms NXT
//
///////////////////////////////////////////////////////////////////////////////
//Copyright (c) 2012 - 2014 Brandon Sanders <brandon@mechakana.com>
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
#ifndef UPGRADEDJOYSTICK_H_
#define UPGRADEDJOYSTICK_H_

#include <JoystickDriver.c>

//Automatically start the joystick driver when this file is included.
#pragma autoStartTasks

//File version format: MM.DD.YYYY
#define upgradedJoystick_version "12.5.2012"

//Global Variables/////////////////////////////////////////////////////////////

//User-accessable values for the joysticks.
TJoystick upJoystick;

//Absolute value for the joysticks.
TJoystick absoluteJoystick;

//Self-explanatory; true if joysticks 1 and 2 are flipped, and false otherwise.
bool joystickFlipped = false;

//Automatic joystick background task status.  True = On, False = Off
bool joystickAutoUpdating = true;

//Functions////////////////////////////////////////////////////////////////////
void disableUpJoystickAuto();
void enableUpJoystickAuto();

short upJoy1Btn(int btn);
short upJoy2Btn(int btn);

void flipJoystick(bool status);

task getUpJoystickAuto();

void getUpJoystick();

//Function: disableUpJoystickAuto//////////////////////////////////////////////
//
//Disables auto updating of joystick values, allowing them to be set manually.
//
void disableUpJoystickAuto()
{
	joystickAutoUpdating = false;
}

//Function: enableUpJoystickAuto///////////////////////////////////////////////
//
//Enables auto updating of joystick values.
//
void enableUpJoystickAuto()
{
	joystickAutoUpdating = true;
}

//Function: upJoy1Btn//////////////////////////////////////////////////////////
//
//[upJoy1Btn] will check if the button on joystick 1 indexed to the passed value
//            is being pressed.
//
//[upJoy1Btn] will return true if it is, and false otherwise.
//
short upJoy1Btn(int btn)
{
	//Return the current button(s) being pressed on joystick 1.
	return ((upJoystick.joy1_Buttons & (1 << (btn - 1))) != 0);
}


//Function: upJoy2Btn//////////////////////////////////////////////////////////
//
//[upJoy2Btn] will check if the button on joystick 2 indexed to the passed value
//            is being pressed.
//
//[upJoy2Btn] will return true if it is, and false otherwise.
//
short upJoy2Btn(int btn)
{
	//Return the current button(s) being pressed on joystick 2.
	return ((upJoystick.joy2_Buttons & (1 << (btn - 1))) != 0);
}

//Function: flipJoystick///////////////////////////////////////////////////////
//
//[flipJoystick] flips the joysticks.  joy1 becomes joy2 and so on.
//
//[flipJoystick] takes a single boolean value.
//               A value of True will enable flipped joysticks, whereas a
//               value of False will disable flipped joysticks.
//
void flipJoystick(bool status)
{
	joystickFlipped = status;
}

//Task: getJoystick////////////////////////////////////////////////////////////
//
//[getUpJoystickAuto] retrieves the current joystick values and assigns them to
//                    [upJoystick].
//
//[getUpJoystickAuto] will swap the values of both controllers if [joystickFlipped]
//                    is equal to "true", causing joy1_x1 to equal joy2_x1 and so on.
//
task getUpJoystickAuto()
{
	//Loop forever.
	while (true)
	{
		//Only run when joystick auto updating is enabled.
		if (joystickAutoUpdating == true)
		{
			//Get the current joystick values.
			getJoystickSettings(absoluteJoystick);

			//If our joysticks are not flipped, assign default values to upJoystick.
			if (joystickFlipped == false)
			{
				//Assign new values.
				upJoystick.joy1_x1 = absoluteJoystick.joy1_x1;
				upJoystick.joy1_y1 = absoluteJoystick.joy1_y1;
				upJoystick.joy1_x2 = absoluteJoystick.joy1_x2;
				upJoystick.joy1_y2 = absoluteJoystick.joy1_y2;
				upJoystick.joy1_Buttons = absoluteJoystick.joy1_Buttons;
				upJoystick.joy1_TopHat = absoluteJoystick.joy1_TopHat;

				upJoystick.joy2_x1 = absoluteJoystick.joy2_x1;
				upJoystick.joy2_y1 = absoluteJoystick.joy2_y1;
				upJoystick.joy2_x2 = absoluteJoystick.joy2_x2;
				upJoystick.joy2_y2 = absoluteJoystick.joy2_y2;
				upJoystick.joy2_Buttons = absoluteJoystick.joy2_Buttons;
				upJoystick.joy2_TopHat = absoluteJoystick.joy2_TopHat;
			}

			//If our joysticks are flipped, flip the values assigned to upJoystick.
			else
			{
				//Assign new values.
				upJoystick.joy1_x1 = absoluteJoystick.joy2_x1;
				upJoystick.joy1_y1 = absoluteJoystick.joy2_y1;
				upJoystick.joy1_x2 = absoluteJoystick.joy2_x2;
				upJoystick.joy1_y2 = absoluteJoystick.joy2_y2;
				upJoystick.joy1_Buttons = absoluteJoystick.joy2_Buttons;
				upJoystick.joy1_TopHat = absoluteJoystick.joy2_TopHat;

				upJoystick.joy2_x1 = absoluteJoystick.joy1_x1;
				upJoystick.joy2_y1 = absoluteJoystick.joy1_y1;
				upJoystick.joy2_x2 = absoluteJoystick.joy1_x2;
				upJoystick.joy2_y2 = absoluteJoystick.joy1_y2;
				upJoystick.joy2_Buttons = absoluteJoystick.joy1_Buttons;
				upJoystick.joy2_TopHat = absoluteJoystick.joy1_TopHat;
			}

			//TODO:
			wait1Msec(75);
		}

		//If auto updating is disabled, wait to conserve clock cycles.
		else
		{
			wait1Msec(250);
		}
	}
}

//Function: getUpJoystick//////////////////////////////////////////////////////
//
//[getUpJoystick] is the manual alternative to [getUpJoystickAuto].
//
//[getUpJoystick] cannot be used if automatic joystick updating is on.
//                To disable automatic joystick updating, add the following
//                to your code BEFORE you include this file:
//
//                #define UPJOYSTICK_AUTO_OFF
//
void getUpJoystick()
{
	//To prevent thread collisions, only run if auto updating is disabled.
	if (joystickAutoUpdating == false)
	{
		//Get the current joystick values.
		getJoystickSettings(absoluteJoystick);

		//If our joysticks are not flipped, assign default values to upJoystick.
		if (joystickFlipped == false)
		{
			//Assign new values.
			upJoystick.joy1_x1 = absoluteJoystick.joy1_x1;
			upJoystick.joy1_y1 = absoluteJoystick.joy1_y1;
			upJoystick.joy1_x2 = absoluteJoystick.joy1_x2;
			upJoystick.joy1_y2 = absoluteJoystick.joy1_y2;
			upJoystick.joy1_Buttons = absoluteJoystick.joy1_Buttons;
			upJoystick.joy1_TopHat = absoluteJoystick.joy1_TopHat;

			upJoystick.joy2_x1 = absoluteJoystick.joy2_x1;
			upJoystick.joy2_y1 = absoluteJoystick.joy2_y1;
			upJoystick.joy2_x2 = absoluteJoystick.joy2_x2;
			upJoystick.joy2_y2 = absoluteJoystick.joy2_y2;
			upJoystick.joy2_Buttons = absoluteJoystick.joy2_Buttons;
			upJoystick.joy2_TopHat = absoluteJoystick.joy2_TopHat;
		}

		//If our joysticks are flipped, flip the values assigned to upJoystick.
		else
		{
			//Assign new values.
			upJoystick.joy1_x1 = absoluteJoystick.joy2_x1;
			upJoystick.joy1_y1 = absoluteJoystick.joy2_y1;
			upJoystick.joy1_x2 = absoluteJoystick.joy2_x2;
			upJoystick.joy1_y2 = absoluteJoystick.joy2_y2;
			upJoystick.joy1_Buttons = absoluteJoystick.joy2_Buttons;
			upJoystick.joy1_TopHat = absoluteJoystick.joy2_TopHat;

			upJoystick.joy2_x1 = absoluteJoystick.joy1_x1;
			upJoystick.joy2_y1 = absoluteJoystick.joy1_y1;
			upJoystick.joy2_x2 = absoluteJoystick.joy1_x2;
			upJoystick.joy2_y2 = absoluteJoystick.joy1_y2;
			upJoystick.joy2_Buttons = absoluteJoystick.joy1_Buttons;
			upJoystick.joy2_TopHat = absoluteJoystick.joy1_TopHat;
		}
	}
}

#endif
