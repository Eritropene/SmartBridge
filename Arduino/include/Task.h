#ifndef __TASK__
#define __TASK__
#include "MsgService.h"

/*Template for a Task object with a tick() method for updates*/
class Task {
public:

    /*This method is used by the Scheduler to run Tasks*/
    virtual void tick() = 0;
};

#endif