/**
  * Will Archer & Ayub Mohamed
  * Group 516, 20th October 2020
  * Runs most of the computations
**/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "result.h"
#include "button.h"
#include "compute.h"
#include "led.h"

// define initialisation values
#define MAXINDEX 2

Comm_data init_comm(char new_char, bool new_bool)
{
    Comm_data new_data;
    new_data.comm_char = new_char;
    new_data.success = new_bool;
    return new_data;
}

/** code from Lab3, correctly buffers a charachter to display
    on the UCFK panel. **/
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

/** modified old code from the last version, increments the index of this UCFK,
    taking in the index and returning it **/
uint8_t increment_index (uint8_t index, uint8_t ammo)
{
    if (index >= MAXINDEX) {
        index = 0; // if it will overflow, make sure it doesn't
    } else {
        index++;
    }
    if (ammo <= 0) {  // if you're all out of ammo
      if (index == 0) { // and you're trying to get to shoot
        index = 1;  // go to block, because you can't shoot
      }
    }
    return index;
}

/** modified old code from the last version, decrements the index of this UCFK,
    taking in the index and returning it **/
uint8_t decrement_index (uint8_t index, uint8_t ammo)
{
    if (index <= 0) {
        index = 2; // if it will underflow, make sure it doesn't
    } else {
        index--;
    }
    if (firing_dry(index, ammo)) {
        index = MAXINDEX;  // go to reload, because you can't shoot
    }
    return index;
}

/** when a firearm has no ammo, but you're pulling the trigger, it is reffered
    to as firing dry. This is a check to see if that is happening **/
bool firing_dry (uint8_t index, uint8_t ammo)
{
    if (ammo <= 0 && index == 0) {
      return true;
    } else {
      return false;
    }
}

/** the function that makes sure you cannot see shoot when you are all out **/
uint8_t ammo_check (uint8_t index, uint8_t ammo)
{
    if (firing_dry(index, ammo)) {
      index = 1;
    }
    return index;
}

/** abstraction of navswitch input NORTH/ UP **/
bool press_up (void)
{
  return navswitch_push_event_p (NAVSWITCH_NORTH);
}

/** abstraction of navswitch input SOUTH/ DOWN **/
bool press_down (void)
{
  return navswitch_push_event_p (NAVSWITCH_SOUTH);
}

/** abstraction of navswitch input WEST/ LEFT **/
bool press_left (void)
{
  return navswitch_push_event_p (NAVSWITCH_WEST);
}

/** abstraction of navswitch input EAST/ RIGHT **/
bool press_right (void)
{
  return navswitch_push_event_p (NAVSWITCH_EAST);
}

/** abstraction of pushing in the navswitch **/
bool press_in (void)
{
  return navswitch_push_event_p (NAVSWITCH_PUSH);
}

/** Code to allow this UCFK to recieve actions from the other **/
Comm_data recieve_action (Comm_data Recieved)
{
  if (ir_uart_read_ready_p()) {
      Recieved.success = true;
      Recieved.comm_char = ir_uart_getc();
  }
  return Recieved;
}

/** Code to allow actions to be sent to the other UCFK **/
Comm_data send_action(Comm_data Sent)
{
    ir_uart_putc(Sent.comm_char);
    Sent.success = true;  // make it known that it has sent
    return Sent;
}

/** Activates/ Deactivates LED and returns what game.c is_locked should be **/
bool lock_in (bool is_locked)
{
    if(is_locked) {
      led_set(LED1, 1);
      return true;
    } else {
      led_set(LED1, 0);
      return false;
    }
}
