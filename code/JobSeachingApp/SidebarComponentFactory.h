#ifndef SIDEBARCOMPONENTFACTORY_H
#define SIDEBARCOMPONENTFACTORY_H

#include "SidebarComponent.h"

class SidebarComponentFactory
{
public:
    virtual ~SidebarComponentFactory() {}
    virtual SidebarComponent* createSidebar(QWidget *parent = nullptr) = 0;
};

#endif // SIDEBARCOMPONENTFACTORY_H
