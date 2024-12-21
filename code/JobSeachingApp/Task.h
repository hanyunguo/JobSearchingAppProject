#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <string>

class Task
{
public:
    Task(){}

    // Getters
    virtual QDateTime getDeadline() {return QDateTime();}
    virtual std::string getTaskDescription() {return "";}
    virtual int getPriority() {return 0;}

    // Setters
    virtual void setDeadline(QDateTime deadline){}
    virtual void setTaskDescription(const std::string taskDescription){}
    virtual void setPriority(int priority){}
};

#endif // TASK_H
