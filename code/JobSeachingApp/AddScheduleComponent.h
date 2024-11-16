#ifndef ADDSCHEDULECOMPONENT_H
#define ADDSCHEDULECOMPONENT_H

#include <QWidget>
#include <QDate>
#include "Schedule.h"
#include "Task.h"

class QLineEdit;
class QPushButton;
class QLabel;
class QCheckBox;

class AddScheduleComponent : public QWidget
{
    Q_OBJECT

public:
    // Constructor accepting date and hour
    explicit AddScheduleComponent(const QDate &date, int hour, QWidget *parent = nullptr);

    // Methods to add, delete, and edit schedules
    void addSchedule(const QDate &date, int hour, const Task &task, const std::string &description, bool complete);
    // void deleteSchedule(const Schedule &schedule);
    void editSchedule(const QDate &date, int hour, const Task &task, const std::string &description, bool complete);

signals:
    void scheduleUpdated(); // Signal emitted when a schedule is added, edited, or deleted
    void closePopUp();

private slots:
    void onSaveClicked();
    void onDeleteClicked();

private:
    void setupUI();
    void connectSignals();
    // void loadSchedule();

    // UI elements
    QLabel *timeslotLabel;
    QLineEdit *descriptionEdit;
    QLineEdit *taskEdit;
    QCheckBox *completedCheck;
    QPushButton *saveButton;
    QPushButton *deleteButton;

    // Member variables
    Schedule currentSchedule;
    QDate date;
    int hour;
};

#endif // ADDSCHEDULECOMPONENT_H
