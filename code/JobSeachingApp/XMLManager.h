#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <string>
#include <vector>

#include "Schedule.h"
#include "SimpleTask.h"
#include "PriorityTaskDecorator.h"
#include "Job.h"

class XMLManager
{
public:
    // Singleton instance
    static XMLManager& getInstance();

    // Methods
    bool saveJobXML(const Job &job);
    bool saveTaskXML(Task *task);
    bool saveScheduleXML(const Schedule &schedule);
    bool deleteScheduleXML(const Schedule &schedule);
    bool deleteJobXML(const Job &job);
    bool deleteTaskXML(const Task &task);
    std::vector<Job> readJobXML();
    std::vector<Schedule> readScheduleXML();
    std::vector<Task*> readTaskXML();

private:
    // Constructor
    XMLManager();

    // Instance variables
    static XMLManager xmlManager;
};

#endif // XMLMANAGER_H

