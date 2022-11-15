#include "Scheduler.h"
#include <Arduino.h>

Scheduler::Scheduler(unsigned int maxTasks) {
    max_tasks = maxTasks;
    tasks = (Task**)malloc(max_tasks*sizeof(Task*));
}

void Scheduler::addTask(Task* task) {
    if (task_count < max_tasks) {
        tasks[task_count] = task;
        task_count++;
    }
}

void Scheduler::executeTasks() {
    //execute task
    tasks[index]->run();
    //switch task
    if (index+1 < task_count) {
        index++;
    } else {
        index = 0;
    }
}