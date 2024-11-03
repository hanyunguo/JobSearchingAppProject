#ifndef SIDEBARFACTORY_H
#define SIDEBARFACTORY_H

#include "sidebarComponent.h"
#include <QString>

class sidebarFactory
{
public:
    static sidebarComponent* createSidebar(const QString &pageType, QWidget *parent = nullptr);
};

#endif // SIDEBARFACTORY_H
