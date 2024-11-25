#ifndef SIDEBARCOMPONENTFACTORY_H
#define SIDEBARCOMPONENTFACTORY_H

#include "SidebarComponent.h"

class SidebarComponentFactory
{
public:
    virtual SidebarComponent* createSidebar(QWidget *parent = nullptr) = 0;
    virtual ~SidebarComponentFactory() {}
};

#endif // SIDEBARCOMPONENTFACTORY_H
