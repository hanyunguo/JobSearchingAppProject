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
    mainLayout->addWidget(addTaskButton, Qt::AlignTop, Qt::AlignRight);
    mainLayout->setSpacing(10);

    // Connect the button to the slot
    connect(addTaskButton, &QPushButton::clicked, this, &TaskListComponent::onAddTaskClicked);

    // Initialize jobTable as a member variable
    taskTable = new QTableWidget(this);
    taskTable->setColumnCount(3);
    taskTable->setHorizontalHeaderLabels({"Deadline", "Task Description", "Priority"});

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
