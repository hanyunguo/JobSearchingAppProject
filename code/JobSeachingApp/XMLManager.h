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
    static XMLManager* getInstance();
    static void setInstance(XMLManager* manager){
        xmlManager = manager;
    }
    // Methods
    virtual bool saveJobXML(const Job &job);
    virtual bool saveTaskXML(Task *task);
    virtual bool saveScheduleXML(const Schedule &schedule);

    bool deleteJobXML(const Job &job);
    bool deleteTaskXML(Task* task);
    bool deleteScheduleXML(const Schedule &schedule);

    std::vector<Job> readJobXML();
    std::vector<Schedule> readScheduleXML();
    std::vector<Task*> readTaskXML();

    bool editJobXML(const Job &oldJob, const Job &updatedJob);
    bool editTaskXML(Task* oldTask, Task* updatedTask);
    bool editScheduleXML(const Schedule &oldschedule, Schedule &newschedule);

protected:
    // Constructor
    XMLManager();

private:
    // Instance variables
    static XMLManager* xmlManager;
};

#endif // XMLMANAGER_H
