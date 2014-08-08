//File: definitions.h
//Project: E-03-Rainbow Dash
//Creation Date: Nov 18, 2013
//
//Global include file for all global constants and variables utilized by the
//HDS-XB-Ironwill.
//
//Author: Brandon Sanders <brandon@mechakana.com>
//
///////////////////////////////////////////////////////////////////////////////
//Copyright (c) 2013 Brandon Sanders <brandon@mechakana.com>
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
#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

/*Motor name table/////////////////////////////////////////////////////////////
 *
 * FR = Front Right Drive Motor
 * FL = Front Left Drive Motor
 * BR = Back Right Drive Motor
 * BL = Back left Drive Motor
 *
 * "Right" and "Left" are from the robots perspective.  E.g., the "Right"
 * side is the side to the left of the robot when you are looking at it from the
 * front.
*/

//Global Constants/////////////////////////////////////////////////////////////

//Joystick deadzones.
#define ERROR_TOP 5 //25
#define ERROR_BOTTOM -5 //25

//Crossbow speed and power.
#define CROSSBOW_SPEED_OPEN -50
#define CROSSBOW_SPEED_CLOSE 50

//Boom motor speed and power.
#define BOOM_SPEED_UP 100
#define BOOM_SPEED_DOWN -100//-10

//Bit map definitions for the touch multiplexer (limit switches).
#define MUX1 0x01
#define MUX2 0x02
#define MUX3 0x04
#define MUX4 0x08

//Global Variables/////////////////////////////////////////////////////////////

#endif
