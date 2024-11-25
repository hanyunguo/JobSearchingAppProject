#ifndef ADDSCHEDULECOMPONENT_H
#define ADDSCHEDULECOMPONENT_H

#include <QWidget>
#include <QDate>

#include "Schedule.h"

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
    void addSchedule(const QDate &date, int hour, const std::string &task, const std::string &description, bool complete);
    // void deleteSchedule(const Schedule &schedule);
    void editSchedule(const QDate &date, int hour, const std::string &task, const std::string &description, bool complete);

signals:
    void scheduleUpdated(); // Signal emitted when a schedule is added, edited, or deleted
    void closePopUp();

private slots:
    void onSaveClicked();

private:
    void setupUI();
    void connectSignals();

    // UI elements
    QLabel *timeslotLabel;
    QLineEdit *descriptionEdit;
    QLineEdit *taskEdit;
    QCheckBox *completedCheck;
    QPushButton *saveButton;

    // Member variables
    Schedule currentSchedule;
    QDate date;
    int hour;
};

#endif // ADDSCHEDULECOMPONENT_H
