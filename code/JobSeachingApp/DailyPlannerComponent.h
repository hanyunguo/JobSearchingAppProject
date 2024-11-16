#ifndef DAILYPLANNERCOMPONENT_H
#define DAILYPLANNERCOMPONENT_H

#include <QWidget>
#include <QDate>
#include <vector>
#include <QMap>
#include <QPushButton>
#include <QLabel>

#include "Schedule.h"

class DailyPlannerComponent : public QWidget
{
    Q_OBJECT

public:
    explicit DailyPlannerComponent(QWidget *parent = nullptr);
    void setDate(const QDate &date);
    void loadSchedules();
    QDate getDate();

signals:
    void timeSlotClicked(int hour);

public slots:
    void updateSchedules();

private:
    void setupUI();
    void updateButtons();
    void handleTimeslotClicked(int hour);

    QDate scheduleDate;
    std::vector<Schedule> schedules;           // Use std::vector as per your design
    QMap<int, QPushButton*> timeSlotButtons;   // Key: hour, Value: button
    QLabel *dateLabel;
};

#endif // DAILYPLANNERCOMPONENT_H
