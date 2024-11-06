#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include "Page.h"
#include "SidebarComponent.h"
#include "CalendarViewComponent.h"
#include "DailyPlannerComponent.h"

class CalendarPage : public Page
{
    Q_OBJECT

public:
    explicit CalendarPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
    void handleDateSelected(const QDate &date);

private:
    CalendarViewComponent *calendarViewComponent;

signals:
    // Signal emitted when a page change is requested
    void targetPageRequested(const QDate &date);
};

#endif // CALENDARPAGE_H
