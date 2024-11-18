#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H
#include "Task.h"

class TaskDecorator : public Task
{
protected:
    Task* task;
public:
    TaskDecorator(Task* task) : task(task) {}

    QDateTime getDeadline() const override{
        return task->getDeadline();
    }
    std::string getTaskDescription() const override{
        return task->getTaskDescription();
    }
    int getPriority() const override{
        return 0;
    }

    // Setters
    void setDeadline(QDateTime deadline) override{
        task->setDeadline(deadline);
    };
    void setTaskDescription(const std::string taskDescription) override{
        task->setTaskDescription(taskDescription);
    };
    void setPriority(int priority) override{
        task->setPriority(priority);
    };
};

#endif // TASKDECORATOR_H
