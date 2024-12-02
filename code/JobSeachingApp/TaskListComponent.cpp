#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QTableWidgetItem>

#include "XMLManager.h"
#include "TaskListComponent.h"
#include "AddTaskComponent.h"

TaskListComponent::TaskListComponent(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    updateTaskList();
}
void TaskListComponent::setupUI(){
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Button to add new task
    addTaskButton = new QPushButton("Add New Task", this);
    addTaskButton->setStyleSheet("QPushButton {"
                                "background-color: #4CAF50;"
                                "color: white;"
                                "font-size: 14px;"
                                "border-radius: 5px;"
                                "padding: 10px;"
                                "}");
    addTaskButton->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(addTaskButton, Qt::AlignTop, Qt::AlignRight);
    mainLayout->setSpacing(10);

    // Connect the button to the slot
    connect(addTaskButton, &QPushButton::clicked, this, &TaskListComponent::onAddTaskClicked);

    // Initialize jobTable as a member variable
    taskTable = new QTableWidget(this);
    taskTable->setColumnCount(5);
    taskTable->setHorizontalHeaderLabels({"Deadline", "Task Description", "Priority", "     ", "    "});

    taskTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable direct editing
    mainLayout->addWidget(taskTable);

    setLayout(mainLayout);
}

void TaskListComponent::updateTaskList()
{
    taskTable->setRowCount(0); // Clear existing table data

    taskList = XMLManager::getInstance().readTaskXML();

    int row = 0;
    for (Task* task : taskList)
    {
        taskTable->insertRow(row);

        QString deadlineStr = task->getDeadline().toString("yyyy-MM-dd HH:mm:ss");

        // Create items for each cell
        QTableWidgetItem *deadlineItem = new QTableWidgetItem(deadlineStr);
        QTableWidgetItem *taskDescriptionItem = new QTableWidgetItem(QString::fromStdString(task->getTaskDescription()));
        QTableWidgetItem *priorityItem = new QTableWidgetItem(QString::number(task->getPriority()));

        taskTable->setItem(row, 0, deadlineItem);
        taskTable->setItem(row, 1, taskDescriptionItem);
        taskTable->setItem(row, 2, priorityItem);

        QPushButton *editButton = new QPushButton("Edit", this);
        editButton->setFixedSize(80, 30);   // Set the size of the Edit button
        editButton->setStyleSheet("QPushButton {"
                                  "background-color: #A8E6CF;"  // Light Pastel Green (for Edit)
                                  "color: #424242;"  // Dark Gray text for contrast
                                  "font-size: 12px;"
                                  "font-weight: normal;"
                                  "border-radius: 5px;"
                                  "padding: 6px 14px;"
                                  "border: 1px solid #A8E6CF;"  // Matching border color
                                  "}");
        editButton->setStyleSheet("QPushButton:hover {"
                                  "background-color: #81C8A5;"  // Darker mint (for hover effect)
                                  "}");


        // Create the Delete button
        QPushButton *deleteButton = new QPushButton("Delete", this);
        deleteButton->setFixedSize(80, 30);
        deleteButton->setStyleSheet("QPushButton {"
                                    "background-color: #FFCDD2;"  // Soft Blush Pink (for Delete)
                                    "color: #424242;"  // Dark Gray text for contrast
                                    "font-size: 12px;"
                                    "font-weight: normal;"
                                    "border-radius: 5px;"
                                    "padding: 6px 14px;"
                                    "border: 1px solid #FFCDD2;"  // Matching border color
                                    "}");
        deleteButton->setStyleSheet("QPushButton:hover {"
                                    "background-color: #FFABAB;"  // Soft peach (for hover effect)
                                    "}");

        connect(editButton, &QPushButton::clicked, this, [this, task]() { onEditTaskClicked(task); });
        connect(deleteButton, &QPushButton::clicked, this, [this, task]() { onDeleteTaskClicked(task); });

        taskTable->setCellWidget(row, 3, editButton);
        taskTable->setCellWidget(row, 4, deleteButton);

        row++;
    }

    // Resize columns to fit content
    taskTable->resizeColumnsToContents();
}

void TaskListComponent::onAddTaskClicked()
{
    // Create an instance of AddJobComponent
    AddTaskComponent *addTaskDialog = new AddTaskComponent(this);
    QDialog *dialog = new QDialog(this);

    // Connect the jobUpdated signal to update the job list after the job is added
    connect(addTaskDialog, &AddTaskComponent::taskUpdated, this, &TaskListComponent::updateTaskList);
    connect(addTaskDialog, &AddTaskComponent::closePopUp, dialog, &QDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(addTaskDialog);
    dialog->setLayout(layout);
    dialog->exec();
}

void TaskListComponent::onEditTaskClicked(Task* oldtask)
{
    // Create a dialog for editing the task
    QDialog *editDialog = new QDialog(this);
    editDialog->setWindowTitle("Edit Task");

    QVBoxLayout *layout = new QVBoxLayout(editDialog);

    // Deadline Label and DateTime Setup
    QLabel *deadlineLabel = new QLabel("Deadline:", this);
    deadlineLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    layout->addWidget(deadlineLabel);

    // Create the button to open the calendar
    QPushButton *calendarButton = new QPushButton("Select Deadline", this);
    calendarButton->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    layout->addWidget(calendarButton);

    // Create the calendar widget but hide it initially
    QCalendarWidget *calendarWidget = new QCalendarWidget(this);
    calendarWidget->setGridVisible(true);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->hide();  // Initially hidden
    layout->addWidget(calendarWidget);

    // Pre-populate the deadline if it's already set for the task
    QDateTime taskDeadline = oldtask->getDeadline();
    QLabel *selectedDateLabel = new QLabel("Selected Deadline: " + taskDeadline.toString("yyyy-MM-dd HH:mm:ss"), this);
    selectedDateLabel->setStyleSheet("background-color: #4CAF50; color: white;font-size: 14px;");
    layout->addWidget(selectedDateLabel);

    // TimeEdit for the time portion
    QTimeEdit *timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("HH:mm:ss");
    timeEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    layout->addWidget(timeEdit);

    // Pre-fill the time from the task's current deadline
    timeEdit->setTime(taskDeadline.time());

    // Task Description
    QLabel *taskDescriptionLabel = new QLabel("Task Description:", this);
    taskDescriptionLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    layout->addWidget(taskDescriptionLabel);

    QLineEdit *taskDescriptionEdit = new QLineEdit(QString::fromStdString(oldtask->getTaskDescription()), this);
    taskDescriptionEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    layout->addWidget(taskDescriptionEdit);

    // Completed Checkbox (Priority option)
    QCheckBox *isPriorityTask = new QCheckBox("Is this a Priority Task?", this);
    isPriorityTask->setStyleSheet("QCheckBox::indicator { width: 20px; height: 20px; }");
    layout->addWidget(isPriorityTask);

    // Priority Level
    priorityLabel = new QLabel("Priority Level:", this);
    priorityLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    priorityLabel->setVisible(false);
    layout->addWidget(priorityLabel);

    priorityEdit = new QLineEdit(QString::number(oldtask->getPriority()), this);
    priorityEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    priorityEdit->setVisible(false);
    layout->addWidget(priorityEdit);

    connect(isPriorityTask, &QCheckBox::toggled, this, [this](bool checked){
        priorityLabel->setVisible(checked);
        priorityEdit->setVisible(checked);

    });

    // Save button to save the task information
    QPushButton *saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("background-color: #B0B0B0; color: white; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    saveButton->setFixedWidth(100);  // Fixed width for consistency
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, [this, oldtask, taskDescriptionEdit, timeEdit, editDialog, calendarWidget, selectedDateLabel, isPriorityTask]() {
        // Retrieve updated values from input fields
        QString taskDescription = taskDescriptionEdit->text();
        int priority = 0;
        if(isPriorityTask->isChecked()){
            priority = priorityEdit->text().toInt();
        }
        // Use priorityEdit directly as it is a member of the class
        QTime time = timeEdit->time();  // Get the time from the QTimeEdit

        // Combine date and time to form a new deadline
        QDate selectedDate = calendarWidget->selectedDate();  // Get the selected date from calendar
        QDateTime updatedDeadline = QDateTime(selectedDate, time);  // Create a new QDateTime with date and time

        // Create the Task object with deadline, description, and priority
        Task* updatedTask = new SimpleTask(updatedDeadline, taskDescription.toStdString());

        // If priority is set, wrap the task with PriorityTaskDecorator
        if (priority > 0) {
            updatedTask = new PriorityTaskDecorator(updatedTask, priority);
        }

        // Update the task in the XML
        XMLManager::getInstance().editTaskXML(oldtask, updatedTask);

        // Refresh the task list
        updateTaskList();

        // Close the dialog
        editDialog->accept();
    });

    // Handle calendar button click to show the calendar
    connect(calendarButton, &QPushButton::clicked, [calendarWidget]() {
        calendarWidget->show();  // Show the calendar when button is clicked
    });

    // Connect the calendar selection to update the selected deadline label
    connect(calendarWidget, &QCalendarWidget::selectionChanged, [calendarWidget, timeEdit, selectedDateLabel]() {
        // Get the selected date and the time from the timeEdit widget
        QDate selectedDate = calendarWidget->selectedDate();
        QTime selectedTime = timeEdit->time();

        // Combine the selected date and time into a QDateTime
        QDateTime selectedDateTime = QDateTime(selectedDate, selectedTime);

        // Update the label with the newly selected date and time
        selectedDateLabel->setText("Selected Deadline: " + selectedDateTime.toString("yyyy-MM-dd HH:mm:ss"));
    });

    // Connect the timeEdit valueChanged to update the selected deadline label
    connect(timeEdit, &QTimeEdit::timeChanged, [calendarWidget, timeEdit, selectedDateLabel]() {
        // Get the selected date and the time from the timeEdit widget
        QDate selectedDate = calendarWidget->selectedDate();
        QTime selectedTime = timeEdit->time();

        // Combine the selected date and time into a QDateTime
        QDateTime selectedDateTime = QDateTime(selectedDate, selectedTime);

        // Update the label with the newly selected date and time
        selectedDateLabel->setText("Selected Deadline: " + selectedDateTime.toString("yyyy-MM-dd HH:mm:ss"));
    });

    // Show the edit dialog
    editDialog->exec();
}

void TaskListComponent::onDeleteTaskClicked(Task *task)
{
    // Create a custom dialog for the delete confirmation
    QDialog *deleteDialog = new QDialog(this);
    deleteDialog->setWindowTitle("Delete Task");

    // Set dialog layout
    QVBoxLayout *layout = new QVBoxLayout(deleteDialog);

    // Add message text
    QLabel *messageLabel = new QLabel("Are you sure you want to delete this task?", deleteDialog);
    layout->addWidget(messageLabel);

    // Create Yes and No buttons
    QPushButton *yesButton = new QPushButton("Yes", deleteDialog);
    QPushButton *noButton = new QPushButton("No", deleteDialog);

    // Apply button styles with significantly larger sizes
    QString yesButtonStyle = "QPushButton {"
                             "background-color: #A8E6CF;"  // Light Pastel Green (for Edit)
                             "color: #424242;"  // Dark Gray text for contrast
                             "font-size: 16px;"  // Slightly smaller font size
                             "font-weight: bold;"  // Bold text for better visibility
                             "border-radius: 8px;"  // Rounded corners
                             "padding: 10px 20px;"  // Reduced padding for more moderate size
                             "}";

    QString noButtonStyle = "QPushButton {"
                            "background-color: #FFCDD2;"  // Soft Blush Pink (for Delete)
                            "color: #424242;"  // Dark Gray text for contrast
                            "font-size: 16px;"  // Slightly smaller font size
                            "font-weight: bold;"  // Bold text for better visibility
                            "border-radius: 8px;"  // Rounded corners
                            "padding: 10px 20px;"  // Reduced padding for more moderate size
                            "}";

    yesButton->setStyleSheet(yesButtonStyle);
    noButton->setStyleSheet(noButtonStyle);

    // Create a button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yesButton);
    buttonLayout->addWidget(noButton);
    layout->addLayout(buttonLayout);

    // Center the buttons in the dialog
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Adjust margins for spacing around the buttons
    layout->setContentsMargins(50, 20, 50, 20);  // Added top and bottom margins

    // Connect buttons to actions
    connect(yesButton, &QPushButton::clicked, this, [this, task, deleteDialog]() {
        XMLManager::getInstance().deleteTaskXML(task);
        updateTaskList(); // Refresh the job list after deletion
        deleteDialog->accept();  // Close the dialog
    });

    connect(noButton, &QPushButton::clicked, deleteDialog, &QDialog::reject);  // Close the dialog on "No"

    // Execute the dialog
    deleteDialog->exec();
}
