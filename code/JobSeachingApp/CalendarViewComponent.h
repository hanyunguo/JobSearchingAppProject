#ifndef CALENDARVIEWCOMPONENT_H
#define CALENDARVIEWCOMPONENT_H

#include <QWidget>
#include <QDate>

class CalendarViewComponent : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarViewComponent(QWidget *parent = nullptr);

signals:
    void dateSelected(const QDate &date);

private:
    QDate currentMonth;
    void setupCalendar();
};

#endif // CALENDARVIEWCOMPONENT_H
