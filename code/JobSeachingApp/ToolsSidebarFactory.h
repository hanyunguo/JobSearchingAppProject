#ifndef TOOLSSIDEBARFACTORY_H
#define TOOLSSIDEBARFACTORY_H

#include "SidebarComponentFactory.h"

class ToolsSidebarFactory : public SidebarComponentFactory
{
public:
    SidebarComponent* createSidebar(QWidget *parent = nullptr) override;
};

#endif // TOOLSSIDEBARFACTORY_H
