#ifndef DAILYPLANNERCOMPONENT_H
#define DAILYPLANNERCOMPONENT_H

#include <QWidget>
#include <QDate>
#include <vector>
#include <QMap>
#include <QPushButton>
#include "Schedule.h"

class DailyPlannerComponent : public QWidget
{
    Q_OBJECT

public:
    explicit DailyPlannerComponent(QWidget *parent = nullptr);
    void setDate(const QDate &date);
    void loadSchedules(); // Ensure this is declared

signals:
    void timeSlotClicked(int hour);

public slots:
    void updateSchedules();

private:
    void setupUI();
    void updateButtons();

    QDate scheduleDate;
    std::vector<Schedule> schedules;           // Use std::vector as per your design
    QMap<int, QPushButton*> timeSlotButtons;   // Key: hour, Value: button
};

#endif // DAILYPLANNERCOMPONENT_H
