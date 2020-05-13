#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "scheduler.h"

void *InitiateScheduler(void *program_name);
int SendPulse(void *unused);
int CheckPulse(void *signal);
void SignalHandler(int signal);
int NeedsStop(void *scheduler);
void WatchdogTask(int signal);
void RunSched(scheduler_t *scheduler);
void WatchdogStop();

#endif /* WATCHDOG_H */