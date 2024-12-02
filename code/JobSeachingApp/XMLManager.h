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

    bool deleteJobXML(const Job &job);
    bool deleteTaskXML(Task* task);
    bool deleteScheduleXML(const Schedule &schedule);

    std::vector<Job> readJobXML();
    std::vector<Schedule> readScheduleXML();
    std::vector<Task*> readTaskXML();

    void editJobXML(const Job &oldJob, const Job &updatedJob);
    void editTaskXML(Task* oldTask, Task* updatedTask);
    void editScheduleXML(const Schedule &oldschedule, Schedule &newschedule);

private:
    // Constructor
    XMLManager();

    // Instance variables
    static XMLManager xmlManager;
};

#endif // XMLMANAGER_H

