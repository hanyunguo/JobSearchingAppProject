#ifndef DAILYPLANNERPAGE_H
#define DAILYPLANNERPAGE_H

#include "Page.h"
#include "SidebarComponent.h"

class DailyPlannerPage : public Page
{
    Q_OBJECT

public:
    explicit DailyPlannerPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
};

#endif // DAILYPLANNERPAGE_H
