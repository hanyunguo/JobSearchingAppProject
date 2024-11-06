#ifndef TASK_H
#define TASK_H

#include <ctime>
#include <string>

class Task
{
public:
    Task();
    Task(const std::string &taskDescription);
    Task(time_t deadline, const std::string &taskDescription, int priority);

    // Getters
    time_t getDeadline() const;
    std::string getTaskDescription() const;
    int getPriority() const;

    // Setters
    void setDeadline(time_t deadline);
    void setTaskDescription(const std::string &taskDescription);
    void setPriority(int priority);

private:
    time_t deadline;
    std::string taskDescription;
    int priority;
};

#endif // TASK_H
