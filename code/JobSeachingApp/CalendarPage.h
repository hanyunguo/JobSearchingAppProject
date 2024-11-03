#ifndef CALENDARPAGE_H
#define CALENDARPAGE_H

#include "Page.h"
#include "SidebarComponent.h"

class CalendarPage : public Page
{
    Q_OBJECT

public:
    explicit CalendarPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
};

#endif // CALENDARPAGE_H
