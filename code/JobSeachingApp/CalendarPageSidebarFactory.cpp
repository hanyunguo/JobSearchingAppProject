#include "CalendarPageSidebarFactory.h"
#include "CalendarPageSidebar.h"

SidebarComponent* CalendarPageSidebarFactory::createSidebar(QWidget *parent)
{
    return new CalendarPageSidebar(parent);
}
