/**
  * Will Archer & Ayub Mohamed
  * Group 516, 20th October 2020
  * main file for ENCE260 UCFK Assignment. Runs the game.
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

// Important globals
#define MAXINDEX 2
#define PACER_RATE 500

const char error = 'E';

int main (void)
{
    /** The main program in which all else is run on. **/

    // run the initialisation functions
    system_init();
    navswitch_init();
    ir_uart_init();
    pacer_init (PACER_RATE);
    tinygl_init (LOOP_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);

    uint8_t index = 0;    // current index this FK is showing
    bool is_locked = false; // a latch bool to make sure that you can hide your selection
    uint8_t game = 1;     // current 'state' the game is running on
    int8_t ammo = 3;     // ammo count for your charachter

    char actions[3] = {'S','R','B'};  // The options to cycle between when picking

    Comm_data Recieved = init_comm(error, false); // FIND A WAY TO RID ERROR, MAKE IT A NO VALUE!
    Comm_data Sent = init_comm(actions[0], false);

    // game loop
    while (1) {
        while(game <= 100) {
            // cyclic updates
            pacer_wait ();
            navswitch_update ();
            index = ammo_check(index, ammo);

            if (press_left()) {
                is_locked = lock_in(true);
            }

            if (press_right()) {
                is_locked = lock_in(false);
            }
            // code that lies in a module, needs to be updated to run on the module function
            if (press_up() && (!is_locked)) {
                index = increment_index (index, ammo);
            }

            // code that lies in a module, needs to be updated to run on the module function
            if (press_down() && (!is_locked)) {
                index = decrement_index (index, ammo);
            }

            Sent.comm_char = actions[index];
            Recieved = recieve_action(Recieved);

            if (press_in()) {
                Sent = send_action(Sent);
            }

            if(Sent.success && Recieved.success) { // if it has both sent and recieved
                is_locked = lock_in(false);
                ammo =  game_result(Sent, Recieved, ammo);

                Sent.success = false;
                Recieved.success = false;
                Sent.comm_char = actions[0];
                index = ammo_check(index, ammo);
            }

            // end of loop cyclic updates
            if (is_locked){
                display_character('?'); // doesn't like empty chars, so used '?'
            } else {
                display_character(Sent.comm_char);
            }
            tinygl_update ();
        }
    }

}
