#ifndef WATCHDOG_PROG_H
#define WATCHDOG_PROG_H

#include "scheduler.h"

void __attribute__((constructor)) ThreadCreate();


void DogSignalHandler(int signal);
void SignalHandlers(int signal);
void *DogSchedInit(void *unused);
void *InitiateScheduler(char **args, pid_t *pid);
void PostToSem();
void RunSched(scheduler_t *scheduler);

#endif /* WATCHDOG_PROG_H */