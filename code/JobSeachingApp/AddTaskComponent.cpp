#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QTimeEdit>

#include "AddTaskComponent.h"
#include "SimpleTask.h"
#include "PriorityTaskDecorator.h"

AddTaskComponent::AddTaskComponent(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    connectSignals();
}
void AddTaskComponent::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Deadline Label
    QLabel *deadlineLabel = new QLabel("Deadline:", this);
    deadlineLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(deadlineLabel);

    // Create the button to open the calendar
    QPushButton *calendarButton = new QPushButton("Select Deadline", this);
    calendarButton->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    mainLayout->addWidget(calendarButton);

    // Create the calendar widget but hide it initially
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGridVisible(true);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->hide(); // Initially hidden

    mainLayout->addWidget(calendarWidget);

    // Create QTimeEdit widget for time selection
    QTimeEdit *timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm:ss");
    timeEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(timeEdit);

    // Label to show the selected date
    selectedDateLabel = new QLabel("Selected Deadline: None", this);
    selectedDateLabel->setStyleSheet("background-color: #4CAF50; color: white;font-size: 14px;/*color: #4CAF50; font-size: 14px; font-weight: bold;*/");
    mainLayout->addWidget(selectedDateLabel);

    // Handle the button click to show the calendar
    connect(calendarButton, &QPushButton::clicked, [calendarWidget]() {
        // Show the calendar when the button is clicked
        calendarWidget->show();
    });

    // Handle the calendar date selection
    connect(calendarWidget, &QCalendarWidget::clicked, [this, calendarWidget, timeEdit]() {
        // Ensure timeEdit is valid and time is set
        if (timeEdit->time().isValid()) {
            // Get the selected date and the time from the timeEdit widget
            QDate selectedDate = calendarWidget->selectedDate();
            QTime selectedTime = timeEdit->time();

            // Combine the selected date and time into a QDateTime
            QDateTime selectedDateTime = QDateTime(selectedDate, selectedTime);

            // Update the label with the newly selected date and time
            selectedDateLabel->setText("Selected Deadline: " + selectedDateTime.toString("yyyy-MM-dd HH:mm:ss"));
            selectedDeadline = selectedDateTime;

            // Hide the calendar after selection
            calendarWidget->hide();
        } else {
            qDebug() << "Invalid time selected!";
        }
    });

    // Connect the timeEdit valueChanged to update the selected deadline label
    connect(timeEdit, &QTimeEdit::timeChanged, [this, calendarWidget, timeEdit]() {
        // Ensure the calendar date is selected
        QDate selectedDate = calendarWidget->selectedDate();
        if (selectedDate.isValid()) {
            // Combine the selected date and time into a QDateTime
            QTime selectedTime = timeEdit->time();
            QDateTime selectedDateTime = QDateTime(selectedDate, selectedTime);

            // Update the label with the newly selected date and time
            selectedDateLabel->setText("Selected Deadline: " + selectedDateTime.toString("yyyy-MM-dd HH:mm:ss"));
            selectedDeadline = selectedDateTime;  // Store the selected deadline
        }
    });

    // Task Description
    QLabel *taskDescriptionLabel = new QLabel("Task Description:", this);
    taskDescriptionLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(taskDescriptionLabel);

    taskDescriptionEdit = new QLineEdit(this);
    taskDescriptionEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(taskDescriptionEdit);

    // Completed Checkbox
    isPriorityTask = new QCheckBox("Is this a Priority Task?", this);
    isPriorityTask->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px; }");
    mainLayout->addWidget(isPriorityTask);

    // Priority - Initially hidden
    priorityLabel = new QLabel("Priority Level:", this);
    priorityLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    priorityLabel->setVisible(false);  // Hide initially
    mainLayout->addWidget(priorityLabel);

    priorityEdit = new QLineEdit(this);
    priorityEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    priorityEdit->setVisible(false);  // Hide initially
    mainLayout->addWidget(priorityEdit);

    // Connect checkbox to show/hide priority input fields
    connect(isPriorityTask, &QCheckBox::toggled, this, [this](bool checked) {
        priorityLabel->setVisible(checked);  // Show/hide the priority label
        priorityEdit->setVisible(checked);   // Show/hide the priority input field
    });

    // Buttons Layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("background-color: #B0B0B0; color: white; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    saveButton->setFixedWidth(100);  // Fixed width for consistency
    buttonLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonLayout);

    // Set the layout for the component
    setLayout(mainLayout);
}

void AddTaskComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddTaskComponent::onSaveClicked);
}


void AddTaskComponent::addTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority)
{
    // Create the Task object with deadline, description, and priority
    Task *task = new SimpleTask(deadline, taskDescription);

    if(priority > 0){
        task = new PriorityTaskDecorator(task, priority);
    }

    // Save the task using XMLManager
    // XMLManager::getInstance().saveTaskXML(task);
    AddTaskCommand* taskCommand = new AddTaskCommand(task);
    taskCommand->execute();

    // Update the current task
    currentTask = task;

    // Emit the signal to notify that the task has been updated
    emit taskUpdated();
}

void AddTaskComponent::onSaveClicked()
{
    // Ensure selectedDeadline is set before accessing it
    if (!selectedDeadline.isValid()) {
        qDebug() << "No valid deadline selected.";
        return; // Early exit if no valid date is selected
    }

    // Get input values from UI elements
    QString taskDescription = taskDescriptionEdit->text();
    QString priority = priorityEdit->text();
    int priorityInt = priority.toInt();

    addTask(selectedDeadline, taskDescription.toStdString(), priorityInt);

    // Close the component if necessary
    emit closePopUp();
}
