#include "DailyPlannerComponent.h"
#include "AddScheduleComponent.h"
#include "XMLManager.h"
#include <QVBoxLayout>
#include <QDateTime>

DailyPlannerComponent::DailyPlannerComponent(QWidget *parent)
    : QWidget(parent), scheduleDate(QDate::currentDate())
{
    setupUI();
    loadSchedules(); // Calls loadSchedules()
    updateButtons();
}

void DailyPlannerComponent::setDate(const QDate &date)
{
    scheduleDate = date;
    dateLabel->setText(scheduleDate.toString("yyyy-MM-dd"));
    loadSchedules();
    updateButtons();
}

void DailyPlannerComponent::updateSchedules()
{
    loadSchedules();
    updateButtons();
}

void DailyPlannerComponent::loadSchedules()
{
    // Clear existing schedules
    schedules.clear();

    // Use XMLManager to read all schedules
    XMLManager &xmlManager = XMLManager::getInstance();
    std::vector<Schedule> allSchedules = xmlManager.readScheduleXML();

    // Filter schedules for the specific date
    for (const Schedule &schedule : allSchedules)
    {
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(schedule.getTimeslot());
        if (dateTime.date() == scheduleDate)
        {
            schedules.push_back(schedule);
        }
    }
}

void DailyPlannerComponent::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Schedule date label
    dateLabel = new QLabel(scheduleDate.toString("yyyy-MM-dd"), this);
    mainLayout->addWidget(dateLabel);

    // Create buttons for each time slot
    for (int i = 0; i < 24; ++i)
    {
        int hour = (9 + i) % 24; // Start from 9:00

        QString timeText = QString("%1:00").arg(hour, 2, 10, QChar('0'));
        QPushButton *button = new QPushButton(timeText, this);

        timeSlotButtons[hour] = button;

        connect(button, &QPushButton::clicked, [this, hour]() {
            emit timeSlotClicked(hour);
        });

        mainLayout->addWidget(button);
    }

    setLayout(mainLayout);
}

void DailyPlannerComponent::updateButtons()
{
    // Update button labels with task and description
    for (int hour = 0; hour < 24; ++hour)
    {
        QPushButton *button = timeSlotButtons.value(hour);
        if (!button)
            continue;

        // Find schedule for the hour
        bool scheduleFound = false;
        for (const Schedule &schedule : schedules)
        {
            QDateTime dateTime = QDateTime::fromSecsSinceEpoch(schedule.getTimeslot());
            if (dateTime.time().hour() == hour)
            {
                QString labelText = QString("%1:00 - %2: %3")
                .arg(hour, 2, 10, QChar('0'))
                    .arg(QString::fromStdString(schedule.getTask().getTaskDescription()))
                    .arg(QString::fromStdString(schedule.getDescription()));
                button->setText(labelText);
                scheduleFound = true;
                break;
            }
        }

        if (!scheduleFound)
        {
            // Reset to default label
            QString timeText = QString("%1:00").arg(hour, 2, 10, QChar('0'));
            button->setText(timeText);
        }
    }
}

QDate DailyPlannerComponent::getDate()
{
    return scheduleDate;
}
