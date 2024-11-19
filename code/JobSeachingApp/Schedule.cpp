#include "Schedule.h"

Schedule::Schedule()
    : timeslot(0), completed(false)
{
}

Schedule::Schedule(time_t timeslot, const std::string &task, const std::string &description, bool completed)
    : timeslot(timeslot), task(task), description(description), completed(completed)
{
}

time_t Schedule::getTimeslot() const
{
    return timeslot;
}

void Schedule::setTimeslot(time_t timeslot)
{
    this->timeslot = timeslot;
}

std::string Schedule::getTask() const
{
    return task;
}

void Schedule::setTask(const std::string &task)
{
    this->task = task;
}

std::string Schedule::getDescription() const
{
    return description;
}

void Schedule::setDescription(const std::string &description)
{
    this->description = description;
}

bool Schedule::isCompleted() const
{
    return completed;
}

void Schedule::setCompleted(bool completed)
{
    this->completed = completed;
}
