#include "XMLManager.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDir>
#include <QXmlStreamReader>

// Initialize the static instance
XMLManager XMLManager::xmlManager;

XMLManager& XMLManager::getInstance()
{
    return xmlManager;
}

XMLManager::XMLManager()
{
}

bool XMLManager::saveJobXML(const Job &job)
{
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

    qDebug() << QDir::currentPath();
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

    qDebug() << QDir::currentPath();
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
        xmlWriter.writeTextElement("Description", QString::fromStdString(sched.getDescription()));
        xmlWriter.writeTextElement("Completed", sched.isCompleted() ? "true" : "false");

        // Write Task
        xmlWriter.writeStartElement("Task");
        xmlWriter.writeTextElement("TaskName", QString::fromStdString(sched.getTask().getTaskDescription()));
        xmlWriter.writeEndElement(); // End Task

        xmlWriter.writeEndElement(); // End Schedule
    }

    xmlWriter.writeEndElement(); // End Schedules
    xmlWriter.writeEndDocument();

    file.close();
    return true;
}

// Delete a Schedule from XML
bool XMLManager::deleteScheduleXML(const Schedule &schedule)
{
    // Read existing schedules
    std::vector<Schedule> schedules = readScheduleXML();

    // Remove the schedule with the specified timeslot
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
        // Schedule not found
        return false;
    }

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

    // Write remaining schedules to the XML file
    for (const Schedule &sched : schedules)
    {
        xmlWriter.writeStartElement("Schedule");
        xmlWriter.writeTextElement("Timeslot", QString::number(sched.getTimeslot()));
        xmlWriter.writeTextElement("Description", QString::fromStdString(sched.getDescription()));
        xmlWriter.writeTextElement("Completed", sched.isCompleted() ? "true" : "false");

        // Write Task
        xmlWriter.writeStartElement("Task");
        xmlWriter.writeTextElement("TaskName", QString::fromStdString(sched.getTask().getTaskDescription()));
        xmlWriter.writeEndElement(); // End Task

        xmlWriter.writeEndElement(); // End Schedule
    }

    xmlWriter.writeEndElement(); // End Schedules
    xmlWriter.writeEndDocument();

    file.close();
    return true;
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
                        else if (xmlReader.name() == "Task")
                        {
                            Task task;
                            while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "Task"))
                            {
                                if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                                {
                                    if (xmlReader.name() == "TaskName")
                                    {
                                        task.setTaskDescription(xmlReader.readElementText().toStdString());
                                    }
                                }
                                xmlReader.readNext();
                            }
                            schedule.setTask(task);
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
