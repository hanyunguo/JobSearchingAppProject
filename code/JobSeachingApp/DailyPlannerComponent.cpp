#include "DailyPlannerComponent.h"
#include "AddScheduleComponent.h"
#include "XMLManager.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QDialog>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>


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
    XMLManager* xmlManager = XMLManager::getInstance();
    std::vector<Schedule> allSchedules = xmlManager->readScheduleXML();

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
        QWidget *timeslotWidget = new QWidget(this);
        QHBoxLayout *timeslotWidgetLayout = new QHBoxLayout(timeslotWidget);

        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));

        // Create the "Edit" button
        QPushButton *editButton = new QPushButton("Edit", this);
        editButton->setFixedSize(80, 30);
        editButton->setStyleSheet("QPushButton {"
                                  "background-color: #A8E6CF;"
                                  "color: #424242;"
                                  "font-size: 12px;"
                                  "font-weight: normal;"
                                  "border-radius: 5px;"
                                  "padding: 6px 14px;"
                                  "border: 1px solid #A8E6CF;"
                                  "}");
        editButton->setStyleSheet("QPushButton:hover {"
                                  "background-color: #81C8A5;"
                                  "}");

        // Create the "Delete" button
        QPushButton *deleteButton = new QPushButton("Delete", this);
        deleteButton->setFixedSize(80, 30);
        deleteButton->setStyleSheet("QPushButton {"
                                    "background-color: #FFCDD2;"
                                    "color: #424242;"
                                    "font-size: 12px;"
                                    "font-weight: normal;"
                                    "border-radius: 5px;"
                                    "padding: 6px 14px;"
                                    "border: 1px solid #FFCDD2;"
                                    "}");
        deleteButton->setStyleSheet("QPushButton:hover {"
                                    "background-color: #FFABAB;"
                                    "}");

        editButton->setVisible(false);
        deleteButton->setVisible(false);

        // Create the timeslot button
        QPushButton *timeSlotButton = new QPushButton(timeText, this);
        timeSlotButtons[i] = timeSlotButton;
        editButtons[i] = editButton;
        deleteButtons[i] = deleteButton;
        connect(timeSlotButton, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        // Connect the edit and delete buttons
        connect(editButton, &QPushButton::clicked, this, [this, i]() { onEditScheduleClicked(i); });
        connect(deleteButton, &QPushButton::clicked, this, [this, i]() { onDeleteScheduleClicked(i); });

        // Add buttons to the layout
        timeslotWidgetLayout->addWidget(editButton);
        timeslotWidgetLayout->addWidget(deleteButton);
        timeslotWidgetLayout->addWidget(timeSlotButton);

        // Add the timeslot widget to the main layout
        timeslotLayout->addWidget(timeslotWidget);
    }

    // Create a QScrollArea to allow scrolling for the remaining timeslots (16:00 to 8:00)
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(timeslotContainer);
    scrollArea->setWidgetResizable(true);

    // Create buttons for timeslots from 16:00 to 23:00
    for (int i = 16; i < 24; ++i) // 16:00 to 23:00
    {
        QWidget *timeslotWidget = new QWidget(this);
        QHBoxLayout *timeslotWidgetLayout = new QHBoxLayout(timeslotWidget);

        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));

        // Create the "Edit" button
        QPushButton *editButton = new QPushButton("Edit", this);
        editButton->setFixedSize(80, 30);
        editButton->setStyleSheet("QPushButton {"
                                  "background-color: #A8E6CF;"
                                  "color: #424242;"
                                  "font-size: 12px;"
                                  "font-weight: normal;"
                                  "border-radius: 5px;"
                                  "padding: 6px 14px;"
                                  "border: 1px solid #A8E6CF;"
                                  "}");
        editButton->setStyleSheet("QPushButton:hover {"
                                  "background-color: #81C8A5;"
                                  "}");

        // Create the "Delete" button
        QPushButton *deleteButton = new QPushButton("Delete", this);
        deleteButton->setFixedSize(80, 30);
        deleteButton->setStyleSheet("QPushButton {"
                                    "background-color: #FFCDD2;"
                                    "color: #424242;"
                                    "font-size: 12px;"
                                    "font-weight: normal;"
                                    "border-radius: 5px;"
                                    "padding: 6px 14px;"
                                    "border: 1px solid #FFCDD2;"
                                    "}");
        deleteButton->setStyleSheet("QPushButton:hover {"
                                    "background-color: #FFABAB;"
                                    "}");

        editButton->setVisible(false);
        deleteButton->setVisible(false);

        // Create the timeslot button
        QPushButton *timeSlotButton = new QPushButton(timeText, this);
        timeSlotButtons[i] = timeSlotButton;
        editButtons[i] = editButton;
        deleteButtons[i] = deleteButton;
        connect(timeSlotButton, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        // Connect the edit and delete buttons
        connect(editButton, &QPushButton::clicked, this, [this, i]() { onEditScheduleClicked(i); });
        connect(deleteButton, &QPushButton::clicked, this, [this, i]() { onDeleteScheduleClicked(i); });

        // Add buttons to the layout
        timeslotWidgetLayout->addWidget(editButton);
        timeslotWidgetLayout->addWidget(deleteButton);
        timeslotWidgetLayout->addWidget(timeSlotButton);

        // Add the timeslot widget to the main layout
        timeslotLayout->addWidget(timeslotWidget);
    }

    // Add a section for 00:00 to 8:00 slots outside of the visible area
    for (int i = 0; i < 9; ++i) // 00:00 to 08:00
    {
        QWidget *timeslotWidget = new QWidget(this);
        QHBoxLayout *timeslotWidgetLayout = new QHBoxLayout(timeslotWidget);

        QString timeText = QString("%1:00").arg(i, 2, 10, QChar('0'));

        // Create the "Edit" button
        QPushButton *editButton = new QPushButton("Edit", this);
        editButton->setFixedSize(80, 30);
        editButton->setStyleSheet("QPushButton {"
                                  "background-color: #A8E6CF;"
                                  "color: #424242;"
                                  "font-size: 12px;"
                                  "font-weight: normal;"
                                  "border-radius: 5px;"
                                  "padding: 6px 14px;"
                                  "border: 1px solid #A8E6CF;"
                                  "}");
        editButton->setStyleSheet("QPushButton:hover {"
                                  "background-color: #81C8A5;"
                                  "}");

        // Create the "Delete" button
        QPushButton *deleteButton = new QPushButton("Delete", this);
        deleteButton->setFixedSize(80, 30);
        deleteButton->setStyleSheet("QPushButton {"
                                    "background-color: #FFCDD2;"
                                    "color: #424242;"
                                    "font-size: 12px;"
                                    "font-weight: normal;"
                                    "border-radius: 5px;"
                                    "padding: 6px 14px;"
                                    "border: 1px solid #FFCDD2;"
                                    "}");
        deleteButton->setStyleSheet("QPushButton:hover {"
                                    "background-color: #FFABAB;"
                                    "}");

        editButton->setVisible(false);
        deleteButton->setVisible(false);

        // Create the timeslot button
        QPushButton *timeSlotButton = new QPushButton(timeText, this);
        timeSlotButtons[i] = timeSlotButton;
        editButtons[i] = editButton;
        deleteButtons[i] = deleteButton;
        connect(timeSlotButton, &QPushButton::clicked, [this, i]() {
            emit handleTimeslotClicked(i);
        });

        // Connect the edit and delete buttons
        connect(editButton, &QPushButton::clicked, this, [this, i]() { onEditScheduleClicked(i); });
        connect(deleteButton, &QPushButton::clicked, this, [this, i]() { onDeleteScheduleClicked(i); });

        // Add buttons to the layout
        timeslotWidgetLayout->addWidget(editButton);
        timeslotWidgetLayout->addWidget(deleteButton);
        timeslotWidgetLayout->addWidget(timeSlotButton);

        // Add the timeslot widget to the main layout
        timeslotLayout->addWidget(timeslotWidget);
    }

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

void DailyPlannerComponent::updateButtons()
{
    for (int hour = 0; hour < 24; ++hour)
    {
        editButtons.value(hour)->setVisible(false);
        deleteButtons.value(hour)->setVisible(false);
    }

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
                editButtons.value(hour)->setVisible(true);
                deleteButtons.value(hour)->setVisible(true);
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

bool DailyPlannerComponent::onEditScheduleClicked(int hour)
{
    bool result;
    // Find the schedule for the specified hour
    Schedule existingSchedule;
    for (const Schedule &schedule : schedules)
    {
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(schedule.getTimeslot());
        if (dateTime.time().hour() == hour)
        {
            existingSchedule = schedule;
            break;
        }
    }

    // Create a new dialog to edit schedule details
    QDialog *editDialog = new QDialog(this);
    editDialog->setWindowTitle("Edit Schedule");

    QVBoxLayout *layout = new QVBoxLayout(editDialog);

    // Create form fields with current schedule details
    QLineEdit *taskEdit = new QLineEdit(QString::fromStdString(existingSchedule.getTask()), editDialog);
    QLineEdit *descriptionEdit = new QLineEdit(QString::fromStdString(existingSchedule.getDescription()), editDialog);
    QCheckBox *completedCheck = new QCheckBox("Completed", editDialog);
    completedCheck->setChecked(existingSchedule.isCompleted());

    // Add widgets to layout
    layout->addWidget(new QLabel("Task:"));
    layout->addWidget(taskEdit);
    layout->addWidget(new QLabel("Description:"));
    layout->addWidget(descriptionEdit);
    layout->addWidget(completedCheck);

    // Save button to update the schedule
    QPushButton *saveButton = new QPushButton("Save", editDialog);
    layout->addWidget(saveButton);

    // When save is clicked, update the schedule and refresh the list
    connect(saveButton, &QPushButton::clicked, this, [this, taskEdit, descriptionEdit, completedCheck, existingSchedule, editDialog, &result]() {
        // Create an updated schedule object with new details from the form
        Schedule updatedSchedule(existingSchedule.getTimeslot(),
                                 taskEdit->text().toStdString(),
                                 descriptionEdit->text().toStdString(),
                                 completedCheck->isChecked());

        // Pass both existingSchedule and updatedSchedule to the XMLManager for editing
        result = XMLManager::getInstance()->editScheduleXML(existingSchedule, updatedSchedule);

        // Refresh the schedule list
        updateSchedules();

        // Close the edit dialog
        editDialog->accept();
    });

    // Execute the dialog
    editDialog->exec();
    return result;
}

bool DailyPlannerComponent::onDeleteScheduleClicked(int hour)
{
    bool result = false;
    // Find the schedule for the specified hour
    Schedule scheduleToDelete;
    for (const Schedule &schedule : schedules)
    {
        QDateTime dateTime = QDateTime::fromSecsSinceEpoch(schedule.getTimeslot());
        if (dateTime.time().hour() == hour)
        {
            scheduleToDelete = schedule;
            break;
        }
    }

    // Show confirmation dialog
    QDialog *deleteDialog = new QDialog(this);
    deleteDialog->setWindowTitle("Delete Schedule");

    QVBoxLayout *layout = new QVBoxLayout(deleteDialog);

    QLabel *messageLabel = new QLabel("Are you sure you want to delete this schedule?", deleteDialog);
    layout->addWidget(messageLabel);

    QPushButton *yesButton = new QPushButton("Yes", deleteDialog);
    QPushButton *noButton = new QPushButton("No", deleteDialog);

    yesButton->setStyleSheet("QPushButton {background-color: #A8E6CF; color: #424242;}");
    noButton->setStyleSheet("QPushButton {background-color: #FFCDD2; color: #424242;}");

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yesButton);
    buttonLayout->addWidget(noButton);
    layout->addLayout(buttonLayout);

    connect(yesButton, &QPushButton::clicked, this, [this, scheduleToDelete, deleteDialog, &result]() {
        // Call XMLManager to delete the schedule from the XML file
        result = XMLManager::getInstance()->deleteScheduleXML(scheduleToDelete);
        updateSchedules();  // Refresh the schedule list
        deleteDialog->accept();  // Close the dialog
    });

    connect(noButton, &QPushButton::clicked, deleteDialog, &QDialog::reject);

    deleteDialog->exec();
    return result;
}
