#ifndef TASKLISTCOMPONENT_H
#define TASKLISTCOMPONENT_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCalendarWidget>
#include <QDateTime>
#include <QTimeEdit>
#include <QCheckBox>

#include "Task.h"

class TaskListComponent : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListComponent(QWidget *parent = nullptr);

public slots:
    void onAddTaskClicked();
    void updateTaskList();
    bool onEditTaskClicked(Task* oldtask);
    bool onDeleteTaskClicked(Task* task);

private:
    void setupUI();

    QTableWidget *taskTable;
    QPushButton *addTaskButton;
    std::vector<Task*> taskList;
    QLineEdit *priorityEdit;
    QLabel *priorityLabel;
    QCheckBox *showPriorityCheckBox;
};

#endif // TASKLISTCOMPONENT_H
