#ifndef DAILYPLANNERPAGESIDEBAR_H
#define DAILYPLANNERPAGESIDEBAR_H

#include "SidebarComponent.h"

class DailyPlannerPageSidebar : public SidebarComponent
{
    Q_OBJECT

public:
    explicit DailyPlannerPageSidebar(QWidget *parent = nullptr);
    void setupSidebar() override;
};

#endif
