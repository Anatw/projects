#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "scheduler.h"

void __attribute__((constructor)) CreateUserThread();

void *UserInitiateScheduler(void *program_name);
void *WatchdogInitiateScheduler(void *program_name);
int UserSendPulse(void *scheduler);
int WatchdogSendPulse(void *scheduler);
int UserCheckPulse(void *program_name);
int WatchdogCheckPulse(void *program_name);
void SignalHandler(int signal);
int NeedsStop(void *scheduler);
void WatchdogTask(int signal);
void RunSched(scheduler_t *scheduler);
void WatchdogStop();
void *UserThread(void *program_name);
void PostToSem();

void SignalHandlers(int signal);
void RestartProcesses();
int GeneralSendPulse(void *pid);
int GeneralCheckPulse(void *program_name);

#endif /* WATCHDOG_H */