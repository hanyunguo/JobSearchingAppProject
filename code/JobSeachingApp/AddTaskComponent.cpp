#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QTimeEdit>

#include "AddTaskComponent.h"
#include "XMLManager.h"
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
    mainLayout->addWidget(deadlineLabel);

    // Create the button to open the calendar
    QPushButton *calendarButton = new QPushButton("Select Deadline", this);
    mainLayout->addWidget(calendarButton);

    // Create the calendar widget but hide it initially
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGridVisible(true);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->hide(); // Initially hidden
    mainLayout->addWidget(calendarWidget);

    // Create QTimeEdit widget for time selection
    QTimeEdit *timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm:ss");  // Set the format for time
    mainLayout->addWidget(timeEdit);

    // Label to show the selected date
    selectedDateLabel = new QLabel("Selected Deadline: None", this);
    mainLayout->addWidget(selectedDateLabel);

    // Handle the button click to show the calendar
    connect(calendarButton, &QPushButton::clicked, [calendarWidget]() {
        // Show the calendar when the button is clicked
        calendarWidget->show();
    });

    // Handle the calendar date selection
    connect(calendarWidget, &QCalendarWidget::clicked, [this, calendarWidget, timeEdit](const QDate &date) {
        // Ensure timeEdit is valid and time is set
        if (timeEdit->time().isValid()) {
            QString formattedDate = date.toString("yyyy-MM-dd");
            QString formattedTime = timeEdit->time().toString("HH:mm:ss");  // Get the selected time from QTimeEdit
            QString formattedDeadline = formattedDate + " " + formattedTime;

            // Update the label to show the selected deadline
            selectedDateLabel->setText("Selected Deadline: " + formattedDeadline);

            // store the selected date and time for further use
            selectedDeadline = QDateTime(date, timeEdit->time());

            // Hide the calendar after selection
            calendarWidget->hide();
        } else {
            qDebug() << "Invalid time selected!";
        }
    });

    // Task Description
    QLabel *taskDescriptionLabel = new QLabel("Task Description:", this);
    mainLayout->addWidget(taskDescriptionLabel);

    taskDescriptionEdit = new QLineEdit(this);
    mainLayout->addWidget(taskDescriptionEdit);

    // Priority
    QLabel *priorityLabel = new QLabel("Priority:", this);
    mainLayout->addWidget(priorityLabel);

    priorityEdit = new QLineEdit(this);
    mainLayout->addWidget(priorityEdit);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save", this);
    buttonLayout->addWidget(saveButton);

    deleteButton = new QPushButton("Delete", this);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void AddTaskComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddTaskComponent::onSaveClicked);
    connect(deleteButton, &QPushButton::clicked, this, &AddTaskComponent::onDeleteClicked);
}


void AddTaskComponent::addTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority)
{
    // Create the Task object with deadline, description, and priority
    Task task = SimpleTask(deadline, taskDescription);

    if(priority > 0){
        task = PriorityTaskDecorator(&task, priority);
    }

    // Save the task using XMLManager
    XMLManager::getInstance().saveTaskXML(task);

    // Update the current task
    currentTask = task;

    // Emit the signal to notify that the task has been updated
    emit taskUpdated();
}

void AddTaskComponent::editTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority)
{
    // Update the current task
    // currentTask.setDeadline(deadline);
    // currentTask.setTaskDescription(taskDescription);
    // currentTask.setPriority(priority);

    // Save the updated task using XMLManager
    // XMLManager::getInstance().saveTaskXML(currentTask);

    // Emit the signal to notify that the task has been updated
    emit taskUpdated();
}

void AddTaskComponent::deleteTask(const Task &task)
{
    // Delete the task using XMLManager
    // XMLManager::getInstance().deletetaskXML(task);

    // Clear the current task
    // currentTask = Task();

    // Emit the signal to notify that the task has been updated
    emit taskUpdated();

    close();
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

void AddTaskComponent::onDeleteClicked()
{
    // Close the component if necessary
    emit closePopUp();
}
