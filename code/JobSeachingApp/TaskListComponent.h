#ifndef TASKLISTCOMPONENT_H
#define TASKLISTCOMPONENT_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

#include "Task.h"

class TaskListComponent : public QWidget
{
    Q_OBJECT
public:
    explicit TaskListComponent(QWidget *parent = nullptr);

public slots:
    void onAddTaskClicked();
    void updateTaskList();

private:
    void setupUI();

    QTableWidget *taskTable;
    QPushButton *addTaskButton;
    std::vector<Task> taskList;
};

#endif // TASKLISTCOMPONENT_H
