/*******************************************************************************
Please ay attention:
1. if either your progarm (when beeing watched by the watchdog), or the watchdog proocess are crashing (and relaunching by the current watchdog library), when your process finished running complitly you might need to press "enter" or any other key to return to the terminal.
2. the signal SIGUSER1 is in use of this programm - you can not use it in your code.

                          Watchdog - test file
                          Written by Anat Wax
                       May 10th - May 16th, 2020
                         Reviewer: Haim Sa'adia
*******************************************************************************/

#ifndef WATCHDOG_H
#define WATCHDOG_H

/*
 * Function to activate the watchdog - a process that will make sure your 
 * program is not exiting unless you use the function WatchdogStop().
 * return: status - 0 - watchdog process launch with success.
 *                  1 - an error has occured while running the process.
 * Arguments: program_name - pointer to string literal of your program name.
 * Compexity: O(1)
 */
 
int WatchdogStart(char *program_name);

/*
 * Function to stop the watchdog. Thie function doesn't stop your process, just 
 * the watchdog itself.
 * Compexity: O(1)
 */
 void WatchdogStop();

#endif /* WATCHDOG_H */
