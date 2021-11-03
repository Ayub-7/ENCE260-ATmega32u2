/**
  * Will Archer & Ayub Mohamed
  * Group 516, 20th October 2020
  * Runs most of the computations
**/

#ifndef COMPUTE_H
#define COMPUTE_H

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "result.h"
#include "button.h"

/** Comm_data struct definition **/
typedef struct comms_data {
    char comm_char;
    bool success;
} Comm_data;

/** Initialises a Comm_data struct **/
Comm_data init_comm(char new_char, bool new_bool);

/** code from Lab3, correctly buffers a charachter to display
    on the UCFK panel. **/
void display_character (char character);

/** modified old code from the last version, increments the index of this UCFK,
    taking in the index and returning it **/
uint8_t increment_index (uint8_t index, uint8_t ammo);

/** modified old code from the last version, decrements the index of this UCFK,
    taking in the index and returning it **/
uint8_t decrement_index (uint8_t index, uint8_t ammo);

/** when a firearm has no ammo, but you're pulling the trigger, it is reffered
    to as firing dry. This is a check to see if that is happening **/
bool firing_dry (uint8_t index, uint8_t ammo);

/** the function that makes sure you cannot see shoot when you are all out **/
uint8_t ammo_check (uint8_t index, uint8_t ammo);

/** abstraction of navswitch input NORTH/ UP **/
bool press_up (void);

/** abstraction of navswitch input SOUTH/ DOWN **/
bool press_down (void);

/** abstraction of navswitch input WEST/ LEFT **/
bool press_left (void);

/** abstraction of navswitch input EAST/ RIGHT **/
bool press_right (void);

/** abstraction of pushing in the navswitch **/
bool press_in (void);

/** Code to allow this UCFK to recieve actions from the other **/
Comm_data recieve_action (Comm_data Recieved);

/** Code to allow actions to be sent to the other UCFK **/
Comm_data send_action(Comm_data Sent);

/** Activates/ Deactivates LED and returns what game.c is_locked should be **/
bool lock_in (bool is_locked);

#endif
