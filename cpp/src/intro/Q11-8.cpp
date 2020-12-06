#include <iostream> /* cout, cin, cerr */
#include <dlfcn.h> /* dlopen(), dlsym(), dlclose() */

#include "scheduler.h"

int main()
{
    scheduler_t *scheduler = SchedulerCreate();

    return (0);
}