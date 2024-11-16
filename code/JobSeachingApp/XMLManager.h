#ifndef XMLMANAGER_H
#define XMLMANAGER_H

#include <string>
#include <vector>

#include "Schedule.h"
#include "Task.h"
#include "Job.h"

class XMLManager
{
public:
    // Singleton instance
    static XMLManager& getInstance();

    // Methods
    bool saveJobXML(const Job &job);
    bool saveTaskXML(const Task &task);
    bool saveScheduleXML(const Schedule &schedule);
    bool deleteScheduleXML(const Schedule &schedule);
    std::vector<Job> readJobXML();
    std::vector<Schedule> readScheduleXML();

private:
    // Constructor
    XMLManager();

    // Disallow copying
    // XMLManager(const XMLManager&) = delete;
    // XMLManager& operator=(const XMLManager&) = delete;

    // Instance variables
    static XMLManager xmlManager;
};

#endif // XMLMANAGER_H
