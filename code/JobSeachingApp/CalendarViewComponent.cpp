// CalendarViewComponent.cpp
#include "CalendarViewComponent.h"
#include <QGridLayout>
#include <QPushButton>
#include <QDate>
#include <QLabel>
#include <QLocale>

CalendarViewComponent::CalendarViewComponent(QWidget *parent)
    : QWidget(parent)
{
    currentMonth = QDate::currentDate();
    setupCalendar();
}

void CalendarViewComponent::setupCalendar()
{
    QGridLayout *gridLayout = new QGridLayout(this);

    // Display month and year
    QLabel *monthLabel = new QLabel(currentMonth.toString("MMMM yyyy"), this);
    gridLayout->addWidget(monthLabel, 0, 0, 1, 7, Qt::AlignCenter);

    // Weekday labels
    QStringList weekdays;
    for (int i = 1; i <= 7; ++i)
    {
        weekdays << QLocale().dayName(i, QLocale::ShortFormat); // or QLocale::LongFormat
    }

    for (int i = 0; i < weekdays.size(); ++i)
    {
        QLabel *weekdayLabel = new QLabel(weekdays.at(i), this);
        weekdayLabel->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(weekdayLabel, 1, i);
    }

    // Days
    QDate firstDayOfMonth(currentMonth.year(), currentMonth.month(), 1);
    int startColumn = firstDayOfMonth.dayOfWeek() - 1; // QDate::dayOfWeek(): 1 (Mon) - 7 (Sun)
    int row = 2;
    int column = startColumn;

    int daysInMonth = currentMonth.daysInMonth();

    for (int day = 1; day <= daysInMonth; ++day)
    {
        QDate date(currentMonth.year(), currentMonth.month(), day);
        QPushButton *dayButton = new QPushButton(QString::number(day), this);

        connect(dayButton, &QPushButton::clicked, [this, date]() {
            emit dateSelected(date);
        });

        gridLayout->addWidget(dayButton, row, column);

        column++;
        if (column > 6)
        {
            column = 0;
            row++;
        }
    }

    setLayout(gridLayout);
}
