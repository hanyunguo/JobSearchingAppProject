#ifndef ADDTASKCOMPONENT_H
#define ADDTASKCOMPONENT_H

#include <QWidget>
#include <QDate>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>

#include "Task.h"
#include "XMLManager.h"

class AddTaskComponent : public QWidget
{
    Q_OBJECT
public:
    explicit AddTaskComponent(QWidget *parent = nullptr);
    bool addTask(const QDateTime &deadline, const std::string &taskDescription, const int &priority);
signals:
    void taskUpdated();
    void closePopUp();

private slots:
    void onSaveClicked();

private:
    void setupUI();
    void connectSignals();

    // UI elements
    QLineEdit *deadlineEdit;
    QLineEdit *taskDescriptionEdit;
    QLineEdit *priorityEdit;
    QCheckBox *isPriorityTask;

    QLabel *selectedDateLabel;  // Label to display the selected deadline
    QDateTime selectedDeadline;     // Variable to store the selected date
    QLabel *priorityLabel;

    // Member variables
    Task *currentTask;

    QPushButton *saveButton;
};

#endif // ADDTASKCOMPONENT_H
