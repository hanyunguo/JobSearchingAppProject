#ifndef SIMPLETASK_H
#define SIMPLETASK_H
#include "Task.h"

class SimpleTask : public Task
{
public:
    SimpleTask(){}
    SimpleTask(QDateTime deadline, std::string taskDescription)
        : deadline(deadline), taskDescription(taskDescription)
    {
        // Empty constructor body
    }

    QDateTime getDeadline() const override{
        return deadline;
    }
    std::string getTaskDescription() const override{
        return taskDescription;
    }
    int getPriority() const override {
        return 0;
    }

    // Setters
    void setDeadline(QDateTime deadline) override{
        this->deadline = deadline;
    }
    void setTaskDescription(const std::string taskDescription) override{
        this->taskDescription = taskDescription;
    }
    void setPriority(int priority) override{
        qWarning() << "try to simple task with priority: " << QString::number(priority);
    }
private:
    QDateTime deadline;
    std::string taskDescription;
};

#endif // SIMPLETASK_H
