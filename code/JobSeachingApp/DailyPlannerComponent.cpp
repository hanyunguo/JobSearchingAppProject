#include "DailyPlannerComponent.h"
#include "AddScheduleComponent.h"
#include "XMLManager.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QDialog>
#include <QScrollArea>


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

    // Create a container for the timeslot buttons
    QWidget *timeslotContainer = new QWidget(this);
    QVBoxLayout *timeslotLayout = new QVBoxLayout(timeslotContainer);

    // Create buttons for each time slot from 9:00 to 15:00
    for (int i = 9; i < 16; ++i) // 9:00 to 15:00 (8 slots)
    {
        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));
        QPushButton *button = new QPushButton(timeText, this);

        timeSlotButtons[i] = button;

        connect(button, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        timeslotLayout->addWidget(button);
    }

    // Create a QScrollArea to allow scrolling for the remaining timeslots (16:00 to 8:00)
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(timeslotContainer);
    scrollArea->setWidgetResizable(true);

    // Create buttons for timeslots from 16:00 to 8:00
    for (int i = 16; i < 24; ++i) // 16:00 to 23:00
    {
        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));
        QPushButton *button = new QPushButton(timeText, this);

        timeSlotButtons[i] = button;

        connect(button, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        timeslotLayout->addWidget(button);
    }

    // Add a section for 00:00 to 8:00 slots outside of the visible area
    for (int i = 0; i < 9; ++i) // 00:00 to 08:00
    {
        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));
        QPushButton *button = new QPushButton(timeText, this);

        timeSlotButtons[i] = button;

        connect(button, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        timeslotLayout->addWidget(button);
    }

    mainLayout->addWidget(scrollArea);
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
                    .arg(QString::fromStdString(schedule.getTask()))
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

void DailyPlannerComponent::handleTimeslotClicked(int hour)
{
    AddScheduleComponent *addScheduleComponent = new AddScheduleComponent(scheduleDate, hour, this);
    QDialog *dialog = new QDialog(this);
    connect(addScheduleComponent, &AddScheduleComponent::scheduleUpdated, this, &DailyPlannerComponent::updateSchedules);
    connect(addScheduleComponent, &AddScheduleComponent::closePopUp, dialog, &QDialog::accept);
    // Display the AddScheduleComponent in a modal dialog

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(addScheduleComponent);
    dialog->setLayout(layout);
    dialog->exec();
}
