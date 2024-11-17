#ifndef ADDTASKCOMPONENT_H
#define ADDTASKCOMPONENT_H

#include <QWidget>
#include <QDate>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "Task.h"

class AddTaskComponent : public QWidget
{
    Q_OBJECT
public:
    explicit AddTaskComponent(QWidget *parent = nullptr);
    void addTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority);
    void editTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority);
    void deleteTask(const Task &task);

signals:
    void taskUpdated();
    void closePopUp();

private slots:
    void onSaveClicked();
    void onDeleteClicked();

private:
    void setupUI();
    void connectSignals();

    // UI elements
    QLineEdit *deadlineEdit;
    QLineEdit *taskDescriptionEdit;
    QLineEdit *priorityEdit;

    QLabel *selectedDateLabel;  // Label to display the selected deadline
    QDateTime selectedDeadline;     // Variable to store the selected date

    // Member variables
    Task currentTask;

    QPushButton *saveButton;
    QPushButton *deleteButton;
};

#endif // ADDTASKCOMPONENT_H
