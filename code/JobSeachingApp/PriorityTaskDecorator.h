#ifndef PRIORITYTASKDECORATOR_H
#define PRIORITYTASKDECORATOR_H

#include "TaskDecorator.h"


class PriorityTaskDecorator : public TaskDecorator
{
public:
    PriorityTaskDecorator(Task* task, int priority) : TaskDecorator(task), priority(priority) {}
    int getPriority() const override{
        return priority;
    }

    // Setters
    void setPriority(int priority) override{
        this->priority = priority;
    }

private:
    int priority;
};

#endif // PRIORITYTASKDECORATOR_H
