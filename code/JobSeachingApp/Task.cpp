#include "Task.h"

Task::Task()
    : deadline(QDateTime()), priority(0)
{
}
Task::Task(const std::string &taskDescription)
    : taskDescription(taskDescription)
{
}

Task::Task(QDateTime deadline, const std::string &taskDescription, int priority)
    : deadline(deadline), taskDescription(taskDescription), priority(priority)
{
}

// Getters
QDateTime Task::getDeadline() const { return deadline; }
std::string Task::getTaskDescription() const { return taskDescription; }
int Task::getPriority() const { return priority; }

// Setters
void Task::setDeadline(QDateTime deadline) { this->deadline = deadline; }
void Task::setTaskDescription(const std::string &taskDescription) { this->taskDescription = taskDescription; }
void Task::setPriority(int priority) { this->priority = priority; }
