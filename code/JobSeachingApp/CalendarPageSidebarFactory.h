#ifndef CALENDARPAGESIDEBARFACTORY_H
#define CALENDARPAGESIDEBARFACTORY_H

#include "SidebarComponentFactory.h"

class CalendarPageSidebarFactory : public SidebarComponentFactory
{
public:
    SidebarComponent* createSidebar(QWidget *parent = nullptr) override;
};

#endif // CALENDARPAGESIDEBARFACTORY_H
