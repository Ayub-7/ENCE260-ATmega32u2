/**
  * Will Archer & Ayub Mohamed
  * Group 516, 20th October 2020
  * main file for ENCE260 UCFK Assignment. Runs the game mostly takes care of result comparisons.
**/

#ifndef RESULT_H
#define RESULT_H

#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "pacer.h"
#include "navswitch.h"
#include "task.h"
#include "compute.h"

// Globals that need initialised
#define PACER_RATE 500
#define MESSAGE_RATE 20
#define LOOP_RATE 500

/** sets up tinygl to show the result for the reveal taking result as
    as an input **/
uint8_t show_result(uint8_t result, uint8_t ammo);

/** returns an easily referable code for each outcome **/
uint8_t compare_results(char this_ucfk, char other_ucfk);

/** runs both show_result and compare result so it looks nicer in game.c **/
uint8_t game_result(Comm_data send, Comm_data recieve, uint8_t ammo);

#endif
