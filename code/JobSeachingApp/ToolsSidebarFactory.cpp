#include "ToolsSidebarFactory.h"
#include "ToolsSidebar.h"

SidebarComponent* ToolsSidebarFactory::createSidebar(QWidget *parent)
{
    return new ToolsSidebar(parent);
}
