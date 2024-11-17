#ifndef TASK_H
#define TASK_H

#include <QDateTime>
#include <string>

class Task
{
public:
    Task();
    Task(const std::string &taskDescription);
    Task(QDateTime deadline, const std::string &taskDescription, int priority);

    // Getters
    QDateTime getDeadline() const;
    std::string getTaskDescription() const;
    int getPriority() const;

    // Setters
    void setDeadline(QDateTime deadline);
    void setTaskDescription(const std::string &taskDescription);
    void setPriority(int priority);

private:
    QDateTime deadline;
    std::string taskDescription;
    int priority;
};

#endif // TASK_H
