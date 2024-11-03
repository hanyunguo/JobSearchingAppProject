#ifndef CALENDARPAGESIDEBAR_H
#define CALENDARPAGESIDEBAR_H

#include "SidebarComponent.h"

class CalendarPageSidebar : public SidebarComponent
{
    Q_OBJECT

public:
    explicit CalendarPageSidebar(QWidget *parent = nullptr);
    void setupSidebar() override;
};

#endif // CALENDARPAGESIDEBAR_H
