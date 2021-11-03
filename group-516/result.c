/**
  * Will Archer & Ayub Mohamed
  * Group 516, 20th October 2020
  * main file for ENCE260 UCFK Assignment. Runs the game mostly takes care of result comparisons.
**/
#include "result.h"
#include "system.h"
#include "tinygl.h"
#include "navswitch.h"
#include "compute.h"

// Important globals
#define PACER_RATE 500
#define MESSAGE_RATE 20
#define LOOP_RATE 500

/** sets up tinygl to show the result for the reveal taking result as
    as an input **/
uint8_t show_result(uint8_t result, uint8_t ammo)
{
    uint8_t restart = 0;

    if(result == 1) {  // if our one shoots the other
        char string[] = "WIN";
        tinygl_text(string);
        ammo--;
    }
    if(result == 2 || result == 3) {  // if our one shoots and the other blocks
        char string[] = "BLOCKED";
        tinygl_text(string);
        ammo--;
    }
    if(result == 4) {  // if both of ours shoot
        char string[] = "BOTH SHOT";
        tinygl_text(string);
        ammo--;
    }
    if(result == 5 || result == 7) {  // if you block and nothing happens
        char string[] = "BLOCKING....";
        tinygl_text(string);
    }
    if(result == 6 || result == 8) {  // if you reload and nothing happens
        char string[] = "RELOADING....";
        tinygl_text(string);
        ammo++;
    }
    if(result == 9) {  // if you lose
        char string[] = "LOSS";
        tinygl_text(string);
    }
    if(result == 0) {  // Bad Data, gotta do it again!
        char string[] = "BAD DATA";
        tinygl_text(string);
    }
    while(1) {
        while(restart == 0) { // while the game has not been restarted
            pacer_wait();
            tinygl_update();
            navswitch_update();

            // if someone presses down to restart NOTE WE NEED TO ADD CONTROLS INTO README
            if (press_in()) {
                navswitch_update();
                restart = 1;
            }
        }
        return ammo;
    }

}

/** returns an easily referable code for each outcome **/
uint8_t compare_results(char this_ucfk, char other_ucfk)
{
    if (this_ucfk == 'S' && other_ucfk == 'R') {
        return 1; // if our one shoots the other
    } else if (this_ucfk == 'S' && other_ucfk == 'B') {
        return 2; // if our one shoots and the other blocks
    } else if(this_ucfk == 'B' && other_ucfk == 'S') {
        return 3; // if our one blocks and the other shoots
    } else if (this_ucfk == 'S' && other_ucfk == 'S') {
        return 4; // if both of ours shoot
    } else if (this_ucfk == 'B' && other_ucfk == 'B') {
        return 5; // if both block
    } else if (this_ucfk == 'R' && other_ucfk == 'R') {
        return 6; // if both reload
    } else if (this_ucfk == 'B' && other_ucfk == 'R') {
        return 7; // if both do noting
    } else if (this_ucfk == 'R' && other_ucfk == 'B') {
        return 8; // if both do noting
    } else if (this_ucfk == 'R' && other_ucfk == 'S') {
        return 9; // if YOU lose!
    }
    return 0; // otherwise, it's when this one is shot, and you would lose!
}

/** runs both show_result and compare result so it looks nicer in game.c **/
uint8_t game_result(Comm_data send, Comm_data recieve, uint8_t ammo)
{
    uint8_t result = compare_results(send.comm_char, recieve.comm_char);
    ammo = show_result(result, ammo);
    return ammo;
}
