#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <string>

class Task
{
public:
    Task(){}

    // Getters
    virtual QDateTime getDeadline() const{return QDateTime();}
    virtual std::string getTaskDescription() const{return "";}
    virtual int getPriority() const{return 0;}

    // Setters
    virtual void setDeadline(QDateTime deadline){}
    virtual void setTaskDescription(const std::string taskDescription){}
    virtual void setPriority(int priority){}
};

#endif // TASK_H
