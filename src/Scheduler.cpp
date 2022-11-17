#include "Scheduler.h"
#include <Arduino.h>

Scheduler::Scheduler(unsigned int maxTasks) {
    max_tasks = maxTasks;
    tasks = new Task*[maxTasks];
}

void Scheduler::addTask(Task* task) {
    if (task_count < max_tasks) {
        tasks[task_count] = task;
        task_count++;
    }
}

void Scheduler::executeTasks() {
    for (int i = 0; i < task_count; i++) {
        tasks[i]->run();
    }
}