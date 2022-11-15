#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

/*Scheduler dei task*/
class Scheduler {

    Task** tasks;
    int index = 0;
    unsigned int task_count = 0;
    unsigned int max_tasks;

public:
    Scheduler(unsigned int maxTasks);
    void addTask(Task* task);
    void executeTasks();
};

#endif