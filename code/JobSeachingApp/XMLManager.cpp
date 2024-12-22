#include <QFile>
#include <QXmlStreamWriter>
#include <QDir>
#include <QXmlStreamReader>

#include "XMLManager.h"
#include <QDebug>
// Initialize the static instance
XMLManager* XMLManager::xmlManager;

XMLManager* XMLManager::getInstance()
{
    if(xmlManager == nullptr) {
        xmlManager = new XMLManager();
    }
    return xmlManager;
}

XMLManager::XMLManager()
{
}

bool XMLManager::saveJobXML(const Job &job)
{
    qDebug() << "Here";
    // Read existing jobs
    std::vector<Job> jobs = readJobXML();

    // Remove any existing job with the same company and same application link
    for (auto it = jobs.begin(); it != jobs.end(); ++it)
    {
        if (it->getJobTitle() == job.getJobTitle()
            && it->getCompanyName() == job.getCompanyName()
            && it->getApplicationLink() == job.getApplicationLink())
        {
            jobs.erase(it);
            break;
        }
    }

    // Add the new or updated schedule
    jobs.push_back(job);

    // Open the file for writing (overwrite)
    QFile file("jobs.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Error opening file for writing
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Jobs");

    // Write all jobs to the XML file
    for (const Job &jb : jobs)
    {
        xmlWriter.writeStartElement("Job");
        xmlWriter.writeTextElement("JobTitle", QString::fromStdString(jb.getJobTitle()));
        xmlWriter.writeTextElement("CompanyName", QString::fromStdString(jb.getCompanyName()));
        xmlWriter.writeTextElement("ApplicationLink", QString::fromStdString(jb.getApplicationLink()));
        xmlWriter.writeTextElement("JobDescription", QString::fromStdString(jb.getJobDescription()));

        xmlWriter.writeEndElement(); // End Job
    }

    xmlWriter.writeEndElement(); // End Job
    xmlWriter.writeEndDocument();

    file.close();
    return true;
}

bool XMLManager::saveTaskXML(Task *task)
{
    // Read existing tasks
    std::vector<Task*> tasks = readTaskXML();

    // Remove any existing task with the same description and deadline
    auto it = std::find_if(tasks.begin(), tasks.end(), [task](Task *existingTask) {
        return existingTask->getTaskDescription() == task->getTaskDescription() &&
               existingTask->getDeadline() == task->getDeadline();
    });
    if (it != tasks.end()) {
        tasks.erase(it);  // Remove existing task
    }

    // Add the new or updated task
    tasks.push_back(task);

    // Open the file for writing (overwrite)
    QFile file("tasks.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing tasks.";
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Tasks");

    // Write all tasks to the XML file
    for (Task *tk : tasks) {
        xmlWriter.writeStartElement("Task");

        // Write the formatted deadline to XML
        xmlWriter.writeTextElement("Deadline", tk->getDeadline().toString("yyyy-MM-dd HH:mm:ss"));
        xmlWriter.writeTextElement("TaskDescription", QString::fromStdString(tk->getTaskDescription()));
        xmlWriter.writeTextElement("Priority", QString::number(tk->getPriority()));

        xmlWriter.writeEndElement();  // End Task
    }

    xmlWriter.writeEndElement();  // End Tasks
    xmlWriter.writeEndDocument();

    file.close();
    return true;
}

bool XMLManager::saveScheduleXML(const Schedule &schedule)
{
    // Read existing schedules
    std::vector<Schedule> schedules = readScheduleXML();

    // Remove any existing schedule with the same timeslot
    for (auto it = schedules.begin(); it != schedules.end(); ++it)
    {
        if (it->getTimeslot() == schedule.getTimeslot())
        {
            schedules.erase(it);
            break;
        }
    }

    // Add the new or updated schedule
    schedules.push_back(schedule);

    // Open the file for writing (overwrite)
    QFile file("schedules.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Error opening file for writing
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Schedules");

    // Write all schedules to the XML file
    for (const Schedule &sched : schedules)
    {
        xmlWriter.writeStartElement("Schedule");
        xmlWriter.writeTextElement("Timeslot", QString::number(sched.getTimeslot()));
        xmlWriter.writeTextElement("TaskName", QString::fromStdString(sched.getTask()));
        xmlWriter.writeTextElement("Description", QString::fromStdString(sched.getDescription()));
        xmlWriter.writeTextElement("Completed", sched.isCompleted() ? "true" : "false");

        xmlWriter.writeEndElement(); // End Schedule
    }

    xmlWriter.writeEndElement(); // End Schedules
    xmlWriter.writeEndDocument();

    file.close();
    return true;
}

bool XMLManager::deleteJobXML(const Job &job)
{
    // Read all jobs from the XML
    std::vector<Job> jobs = readJobXML();

    // Find and remove the job that matches the provided job
    auto it = std::remove_if(jobs.begin(), jobs.end(), [&job](const Job &jb) {
        return jb.getJobTitle() == job.getJobTitle() &&
               jb.getCompanyName() == job.getCompanyName() &&
               jb.getApplicationLink() == job.getApplicationLink();
    });

    // If the job was found and removed, `it` will be valid and we can erase it
    if (it != jobs.end())
    {
        jobs.erase(it, jobs.end());  // Remove the job from the vector

        // Open the file for writing (overwrite)
        QFile file("jobs.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error opening file for writing.";
            return false;
        }

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Jobs");

        // Write all remaining jobs back to the XML file
        for (const Job &jb : jobs)
        {
            xmlWriter.writeStartElement("Job");
            xmlWriter.writeTextElement("JobTitle", QString::fromStdString(jb.getJobTitle()));
            xmlWriter.writeTextElement("CompanyName", QString::fromStdString(jb.getCompanyName()));
            xmlWriter.writeTextElement("ApplicationLink", QString::fromStdString(jb.getApplicationLink()));
            xmlWriter.writeTextElement("JobDescription", QString::fromStdString(jb.getJobDescription()));
            xmlWriter.writeEndElement(); // End Job
        }

        xmlWriter.writeEndElement(); // End Jobs
        xmlWriter.writeEndDocument();

        file.close();
        return true;
    }
    else
    {
        qDebug() << "Job not found!";
        return false;
    }
}

// Delete a Schedule from XML
bool XMLManager::deleteScheduleXML(const Schedule &schedule)
{
    std::vector<Schedule> schedules = readScheduleXML();

    bool found = false;
    for (auto it = schedules.begin(); it != schedules.end(); ++it)
    {
        if (it->getTimeslot() == schedule.getTimeslot())
        {
            schedules.erase(it);
            found = true;
            break;
        }
    }

    if (!found)
    {
        return false;  // Schedule not found
    }

    // Save the updated schedules to the XML file
    QFile file("schedules.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Schedules");

    for (const Schedule &sched : schedules)
    {
        xmlWriter.writeStartElement("Schedule");
        xmlWriter.writeTextElement("Timeslot", QString::number(sched.getTimeslot()));
        xmlWriter.writeTextElement("TaskName", QString::fromStdString(sched.getTask()));
        xmlWriter.writeTextElement("Description", QString::fromStdString(sched.getDescription()));
        xmlWriter.writeTextElement("Completed", sched.isCompleted() ? "true" : "false");
        xmlWriter.writeEndElement();  // End Schedule
    }

    xmlWriter.writeEndElement(); // End Schedules
    xmlWriter.writeEndDocument();

    file.close();
    return true;
}

bool XMLManager::deleteTaskXML(Task* task)
{
    // Read all tasks from the XML
    std::vector<Task*> tasks = readTaskXML();

    // Find and remove the task that matches the provided task
    auto it = std::remove_if(tasks.begin(), tasks.end(), [task](Task* t) {
        return t->getTaskDescription() == task->getTaskDescription() &&
               t->getDeadline() == task->getDeadline();
    });

    // If the task was found and removed, `it` will be valid, and we can erase it
    if (it != tasks.end())
    {
        tasks.erase(it, tasks.end());  // Remove the task from the vector

        // Open the file for writing (overwrite)
        QFile file("tasks.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error opening file for writing.";
            return false;
        }

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Tasks");

        // Write all remaining tasks back to the XML file
        for (Task* t : tasks)
        {
            xmlWriter.writeStartElement("Task");

            // Write the formatted deadline to XML
            xmlWriter.writeTextElement("Deadline", t->getDeadline().toString("yyyy-MM-dd HH:mm:ss"));
            xmlWriter.writeTextElement("TaskDescription", QString::fromStdString(t->getTaskDescription()));
            xmlWriter.writeTextElement("Priority", QString::number(t->getPriority()));

            xmlWriter.writeEndElement();  // End Task
        }

        xmlWriter.writeEndElement();  // End Tasks
        xmlWriter.writeEndDocument();

        file.close();
        return true;
    }
    else
    {
        qDebug() << "Task not found!";
        return false;
    }
}

// Read all Schedules from XML
std::vector<Schedule> XMLManager::readScheduleXML()
{
    std::vector<Schedule> schedules;

    // Open the XML file
    QFile file("schedules.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Error opening file for reading; return empty vector
        return schedules;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "Schedule")
            {
                Schedule schedule;
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Schedule"))
                {
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xmlReader.name() == "Timeslot")
                        {
                            schedule.setTimeslot(xmlReader.readElementText().toLongLong());
                        }
                        else if (xmlReader.name() == "Description")
                        {
                            schedule.setDescription(xmlReader.readElementText().toStdString());
                        }
                        else if (xmlReader.name() == "Completed")
                        {
                            schedule.setCompleted(xmlReader.readElementText() == "true");
                        }
                        else if (xmlReader.name() == "TaskName")
                        {
                            schedule.setTask(xmlReader.readElementText().toStdString());
                        }
                    }
                    xmlReader.readNext();
                }
                schedules.push_back(schedule);
            }
        }
    }

    if (xmlReader.hasError())
    {
        // Handle XML read error if necessary
    }

    file.close();
    return schedules;
}

// Read all Jobs from XML
std::vector<Job> XMLManager::readJobXML()
{
    std::vector<Job> jobs;

    // Open the XML file
    QFile file("jobs.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Error opening file for reading; return empty vector
        return jobs;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "Job")
            {
                Job job;
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Job"))
                {
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xmlReader.name() == "JobTitle")
                        {
                            job.setJobTitle(xmlReader.readElementText().toStdString());
                        }
                        else if (xmlReader.name() == "CompanyName")
                        {
                            job.setCompanyName(xmlReader.readElementText().toStdString());
                        }
                        else if (xmlReader.name() == "ApplicationLink")
                        {
                            job.setApplicationLink(xmlReader.readElementText().toStdString());
                        }
                        else if (xmlReader.name() == "JobDescription")
                        {
                            job.setJobDescription(xmlReader.readElementText().toStdString());
                        }
                    }
                    xmlReader.readNext();
                }
                jobs.push_back(job);
            }
        }
    }

    if (xmlReader.hasError())
    {
        // Handle XML read error if necessary
    }

    file.close();
    return jobs;
}

// Read all Tasks from XML
std::vector<Task*> XMLManager::readTaskXML()
{
    std::vector<Task*> tasks;

    // Open the XML file
    QFile file("tasks.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Error opening file for reading; return empty vector
        return tasks;
    }

    QXmlStreamReader xmlReader(&file);

    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();

        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "Task")
            {
                Task *task = new SimpleTask();
                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Task"))
                {
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xmlReader.name() == "Deadline")
                        {
                            // Read the deadline as a string
                            QString deadlineString = xmlReader.readElementText();

                            // Convert the string to QDateTime (assuming the format matches)
                            QDateTime dateTime = QDateTime::fromString(deadlineString, "yyyy-MM-dd HH:mm:ss");
                            task->setDeadline(dateTime);
                        }
                        else if (xmlReader.name() == "TaskDescription")
                        {
                            task->setTaskDescription(xmlReader.readElementText().toStdString());
                        }
                        else if (xmlReader.name() == "Priority")
                        {
                            int p = xmlReader.readElementText().toInt();
                            if(p > 0){
                                task = new PriorityTaskDecorator(task, p);
                            }
                        }
                    }
                    xmlReader.readNext();
                }
                tasks.push_back(task);
            }
        }
    }

    if (xmlReader.hasError())
    {
        // Handle XML read error if necessary
    }

    file.close();
    return tasks;
}

bool XMLManager::editJobXML(const Job &oldJob, const Job &updatedJob)
{
    // Read all jobs from the XML
    std::vector<Job> jobs = readJobXML();

    // Find the job that needs to be updated
    bool jobUpdated = false;
    for (auto &job : jobs)
    {
        // Compare the old job details with the job in the XML
        if (job.getJobTitle() == oldJob.getJobTitle() &&
            job.getCompanyName() == oldJob.getCompanyName() &&
            job.getApplicationLink() == oldJob.getApplicationLink())
        {
            // Update the job details with the new values
            job.setJobTitle(updatedJob.getJobTitle());
            job.setCompanyName(updatedJob.getCompanyName());
            job.setApplicationLink(updatedJob.getApplicationLink());
            job.setJobDescription(updatedJob.getJobDescription());
            jobUpdated = true;
            break;
        }
    }

    // If the job was updated, rewrite the XML file
    if (jobUpdated)
    {
        QFile file("jobs.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error opening file for writing.";
            return jobUpdated;
        }

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Jobs");

        // Write all jobs back to the XML file
        for (const Job &job : jobs)
        {
            xmlWriter.writeStartElement("Job");
            xmlWriter.writeTextElement("JobTitle", QString::fromStdString(job.getJobTitle()));
            xmlWriter.writeTextElement("CompanyName", QString::fromStdString(job.getCompanyName()));
            xmlWriter.writeTextElement("ApplicationLink", QString::fromStdString(job.getApplicationLink()));
            xmlWriter.writeTextElement("JobDescription", QString::fromStdString(job.getJobDescription()));
            xmlWriter.writeEndElement(); // End Job
        }

        xmlWriter.writeEndElement(); // End Jobs
        xmlWriter.writeEndDocument();

        file.close();
    }
    else
    {
        qDebug() << "Job not found!";
    }
    return jobUpdated;
}

bool XMLManager::editTaskXML(Task* oldTask, Task* updatedTask)
{
    // Read all tasks from the XML
    std::vector<Task*> tasks = readTaskXML();

    bool taskUpdated = false;

    // Loop through all tasks to find the one that matches the updated task
    for (auto &task : tasks)
    {
        // Compare task details (description, deadline, priority) to identify the task
        if (task->getTaskDescription() == oldTask->getTaskDescription() &&
            task->getDeadline() == oldTask->getDeadline() && task->getPriority() == oldTask->getPriority())
        {
            // Update the task fields with the new values
            task->setTaskDescription(updatedTask->getTaskDescription());
            if(task->getPriority() == 0 && updatedTask->getPriority() > 0) {
                task = new PriorityTaskDecorator(task, updatedTask->getPriority());
            } else {
                task->setPriority(updatedTask->getPriority());
            }
            task->setDeadline(updatedTask->getDeadline());
            taskUpdated = true;
            break;
        }
    }

    // If the task is found and updated, rewrite the XML file
    if (taskUpdated)
    {
        QFile file("tasks.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Error opening file for writing.";
            return taskUpdated;
        }

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("Tasks");

        // Write all tasks back to the XML file
        for (Task* task : tasks)
        {
            xmlWriter.writeStartElement("Task");

            // Write the formatted deadline to XML
            xmlWriter.writeTextElement("Deadline", task->getDeadline().toString("yyyy-MM-dd HH:mm:ss"));
            xmlWriter.writeTextElement("TaskDescription", QString::fromStdString(task->getTaskDescription()));
            xmlWriter.writeTextElement("Priority", QString::number(task->getPriority()));

            xmlWriter.writeEndElement();  // End Task
        }

        xmlWriter.writeEndElement();  // End Tasks
        xmlWriter.writeEndDocument();

        file.close();
    }
    else
    {
        qDebug() << "Task not found!";
    }
    return taskUpdated;
}

bool XMLManager::editScheduleXML(const Schedule &oldSchedule, Schedule &newSchedule)
{
    std::vector<Schedule> schedules = readScheduleXML();

    bool found = false;
    for (auto &sched : schedules)
    {
        if (sched.getTimeslot() == oldSchedule.getTimeslot())
        {
            sched = newSchedule;
            found = true;
            break;
        }
    }

    if (!found)
    {
        return found;  // Schedule not found, no update
    }

    // Save the updated schedules to the XML file
    QFile file("schedules.xml");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return found;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("Schedules");

    for (const Schedule &sched : schedules)
    {
        xmlWriter.writeStartElement("Schedule");
        xmlWriter.writeTextElement("Timeslot", QString::number(sched.getTimeslot()));
        xmlWriter.writeTextElement("TaskName", QString::fromStdString(sched.getTask()));
        xmlWriter.writeTextElement("Description", QString::fromStdString(sched.getDescription()));
        xmlWriter.writeTextElement("Completed", sched.isCompleted() ? "true" : "false");
        xmlWriter.writeEndElement();  // End Schedule
    }

    xmlWriter.writeEndElement(); // End Schedules
    xmlWriter.writeEndDocument();

    file.close();
    return found;
}
