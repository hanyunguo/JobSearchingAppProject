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
#include "DailyPlannerComponent.h"

AddScheduleComponent::AddScheduleComponent(const QDate &date, int hour, QWidget *parent)
    : QWidget(parent), date(date), hour(hour)
{
    setupUI();
    connectSignals();
    // loadSchedule();
}

void AddScheduleComponent::setupUI()
{
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

    mainLayout->addLayout(buttonLayout);

    // Set the main layout
    setLayout(mainLayout);
}

void AddScheduleComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddScheduleComponent::onSaveClicked);
}

bool AddScheduleComponent::addSchedule(const QDate &date, int hour, const std::string &task, const std::string &description, bool complete)
{    // Create a new Schedule object
    QDateTime dateTime(date, QTime(hour, 0));
    time_t timeslot = dateTime.toSecsSinceEpoch();
    Schedule schedule(timeslot, task, description, complete);

    // Save the schedule using XMLManager
    bool addResult = XMLManager::getInstance()->saveScheduleXML(schedule);

    // Update the current schedule
    currentSchedule = schedule;

    // Emit the signal to notify that the schedule has been updated
    emit scheduleUpdated();
    return addResult;
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
    // Close the component if necessary
    emit closePopUp();
}
