#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

/*Task Scheduler, runs in the main loop*/
class Scheduler {

    Task** tasks;
    unsigned int task_count = 0;
    unsigned int max_tasks;

public:
    /*Crea uno Scheduler con massimo @maxTasks task*/
    Scheduler(unsigned int maxTasks);

    /*Aggiunge un task alla coda dei task, se non piena*/
    void addTask(Task* task);

    /*Esegue i task presenti nella coda*/
    void executeTasks();
};

#endif