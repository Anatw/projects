#ifndef WATCHDOG_H
#define WATCHDOG_H

/* SIGUSER1 is in use of this programm */
int WatchdogStart(char *program_name);
void WatchdogStop();

#endif /* WATCHDOG_H */