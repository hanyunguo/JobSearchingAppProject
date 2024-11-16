#ifndef DAILYPLANNERPAGE_H
#define DAILYPLANNERPAGE_H

#include "Page.h"
#include "SidebarComponent.h"
#include "DailyPlannerComponent.h"

class DailyPlannerPage : public Page
{
    Q_OBJECT

public:
    explicit DailyPlannerPage(QWidget *parent = nullptr);
    void setupPage() override;
    void changeToTargetDate(const QDate &date);

private slots:
    void handleNavigation(const QString &pageName);
    void handleDateChange(const QDate &date);

private:
    DailyPlannerComponent *dailyPlannerComponent;
    SidebarComponent *sidebar;
};

#endif // DAILYPLANNERPAGE_H
