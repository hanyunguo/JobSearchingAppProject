#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "Task.h"
#include <string>
#include <ctime>

class Schedule
{
public:
    // Constructors
    Schedule();
    Schedule(time_t timeslot, const std::string &task, const std::string &description, bool completed);

    bool operator==(const Schedule& other) const {
        return timeslot == other.getTimeslot() && task == other.getTask()
        && description == other.getDescription() && completed == other.isCompleted();
    }

    // Getters and Setters
    time_t getTimeslot() const;
    void setTimeslot(time_t timeslot);

    std::string getTask() const;
    void setTask(const std::string &task);

    std::string getDescription() const;
    void setDescription(const std::string &description);

    bool isCompleted() const;
    void setCompleted(bool completed);

private:
    time_t timeslot;
    std::string task;
    std::string description;
    bool completed;
};

#endif // SCHEDULE_H
