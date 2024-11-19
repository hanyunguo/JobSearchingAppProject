#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QDateTime>

#include "AddScheduleComponent.h"
#include "XMLManager.h"
#include "Schedule.h"

AddScheduleComponent::AddScheduleComponent(const QDate &date, int hour, QWidget *parent)
    : QWidget(parent), date(date), hour(hour)
{
    setupUI();
    connectSignals();
    // loadSchedule();
}

void AddScheduleComponent::setupUI()
{
    // QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // // Timeslot Label
    // timeslotLabel = new QLabel(this);
    // timeslotLabel->setText(QString("Timeslot: %1 %2:00").arg(date.toString("yyyy-MM-dd")).arg(hour));
    // mainLayout->addWidget(timeslotLabel);

    // // Task
    // QLabel *taskLabel = new QLabel("Task:", this);
    // mainLayout->addWidget(taskLabel);

    // taskEdit = new QLineEdit(this);
    // mainLayout->addWidget(taskEdit);

    // // Description
    // QLabel *descriptionLabel = new QLabel("Description:", this);
    // mainLayout->addWidget(descriptionLabel);

    // descriptionEdit = new QLineEdit(this);
    // mainLayout->addWidget(descriptionEdit);

    // // Completed Checkbox
    // completedCheck = new QCheckBox("Completed", this);
    // mainLayout->addWidget(completedCheck);

    // // Buttons
    // QHBoxLayout *buttonLayout = new QHBoxLayout();

    // saveButton = new QPushButton("Save", this);
    // buttonLayout->addWidget(saveButton);

    // deleteButton = new QPushButton("Delete", this);
    // buttonLayout->addWidget(deleteButton);

    // mainLayout->addLayout(buttonLayout);

    // setLayout(mainLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Timeslot Label (No border styling for this label, just clear text)
    timeslotLabel = new QLabel(this);
    timeslotLabel->setText(QString("Timeslot: %1 %2:00").arg(date.toString("yyyy-MM-dd")).arg(hour));
    timeslotLabel->setStyleSheet("color: #333333; font-size: 16px; font-weight: bold;");
    mainLayout->addWidget(timeslotLabel);

    // Task Label
    QLabel *taskLabel = new QLabel("Task:", this);
    taskLabel->setStyleSheet("color: #333333; font-size: 14px;");
    mainLayout->addWidget(taskLabel);

    // Task Input Field
    taskEdit = new QLineEdit(this);
    taskEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(taskEdit);

    // Description Label
    QLabel *descriptionLabel = new QLabel("Description:", this);
    descriptionLabel->setStyleSheet("color: #333333; font-size: 14px;");
    mainLayout->addWidget(descriptionLabel);

    // Description Input Field
    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(descriptionEdit);

    // Completed Checkbox
    completedCheck = new QCheckBox("Completed", this);
    completedCheck->setStyleSheet("color: #333333; font-size: 14px;");
    mainLayout->addWidget(completedCheck);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("background-color: #B0B0B0; color: white; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    saveButton->setFixedWidth(100);
    buttonLayout->addWidget(saveButton);

    deleteButton = new QPushButton("Delete", this);
    deleteButton->setStyleSheet("background-color: #D0D0D0; color: white; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    deleteButton->setFixedWidth(100);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    // Set the main layout
    setLayout(mainLayout);
}

void AddScheduleComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddScheduleComponent::onSaveClicked);
    connect(deleteButton, &QPushButton::clicked, this, &AddScheduleComponent::onDeleteClicked);
}

// void AddScheduleComponent::loadSchedule()
// {
//     // Load existing schedule from XMLManager for the given date and hour
//     XMLManager &xmlManager = XMLManager::getInstance();
//     Schedule schedule = xmlManager.getSchedule(date, hour);

//     if (schedule.getTimeslot() != 0)
//     {
//         // Schedule exists; populate UI fields
//         currentSchedule = schedule;
//         descriptionEdit->setText(QString::fromStdString(schedule.getDescription()));
//         taskEdit->setText(QString::fromStdString(schedule.getTask().getTaskDescription()));
//         completedCheck->setChecked(schedule.isCompleted());
//     }
//     else
//     {
//         // No existing schedule; initialize currentSchedule
//         currentSchedule = Schedule();
//     }
// }

void AddScheduleComponent::addSchedule(const QDate &date, int hour, const std::string &task, const std::string &description, bool complete)
{    // Create a new Schedule object
    QDateTime dateTime(date, QTime(hour, 0));
    time_t timeslot = dateTime.toSecsSinceEpoch();
    Schedule schedule(timeslot, task, description, complete);

    // Save the schedule using XMLManager
    XMLManager::getInstance().saveScheduleXML(schedule);

    // Update the current schedule
    currentSchedule = schedule;

    // Emit the signal to notify that the schedule has been updated
    emit scheduleUpdated();
}

// void AddScheduleComponent::deleteSchedule(const Schedule &schedule)
// {
//     // Delete the schedule using XMLManager
//     XMLManager::getInstance().deleteScheduleXML(schedule);

//     // Clear the current schedule
//     currentSchedule = Schedule();

//     // Emit the signal to notify that the schedule has been updated
//     emit scheduleUpdated();
// }

void AddScheduleComponent::editSchedule(const QDate &date, int hour, const std::string &task, const std::string &description, bool complete)
{
    // Update the current Schedule object
    QDateTime dateTime(date, QTime(hour, 0));
    time_t timeslot = dateTime.toSecsSinceEpoch();

    currentSchedule.setTimeslot(timeslot);
    currentSchedule.setTask(task);
    currentSchedule.setDescription(description);
    currentSchedule.setCompleted(complete);

    // Save the updated schedule using XMLManager
    XMLManager::getInstance().saveScheduleXML(currentSchedule);

    // Emit the signal to notify that the schedule has been updated
    emit scheduleUpdated();
}

void AddScheduleComponent::onSaveClicked()
{
    // Get input values from UI elements
    QString description = descriptionEdit->text();
    QString taskName = taskEdit->text();
    bool completed = completedCheck->isChecked();

    // Create Task object
    if (currentSchedule.getTimeslot() == 0)
    {
        // Adding a new schedule
        addSchedule(date, hour, taskName.toStdString(), description.toStdString(), completed);
    }
    else
    {
        // Editing an existing schedule
        editSchedule(date, hour, taskName.toStdString(), description.toStdString(), completed);
    }

    // Close the component if necessary
    emit closePopUp();
}

void AddScheduleComponent::onDeleteClicked()
{
    if (currentSchedule.getTimeslot() != 0)
    {
        // Delete the current schedule
        // deleteSchedule(currentSchedule);
    }

    // Close the component if necessary
    emit closePopUp();
}
