#ifndef DAILYPLANNERPAGESIDEBARFACTORY_H
#define DAILYPLANNERPAGESIDEBARFACTORY_H

#include "SidebarComponentFactory.h"

class DailyPlannerPageSidebarFactory : public SidebarComponentFactory
{
public:
    SidebarComponent* createSidebar(QWidget *parent = nullptr) override;
};

#endif // DAILYPLANNERPAGESIDEBARFACTORY_H
