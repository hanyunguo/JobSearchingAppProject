#include "DailyPlannerPageSidebarFactory.h"
#include "DailyPlannerPageSidebar.h"

SidebarComponent* DailyPlannerPageSidebarFactory::createSidebar(QWidget *parent)
{
    return new DailyPlannerPageSidebar(parent);
}
