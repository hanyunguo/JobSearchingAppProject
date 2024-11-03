#ifndef TOOLSSIDEBAR_H
#define TOOLSSIDEBAR_H

#include "SidebarComponent.h"

class ToolsSidebar : public SidebarComponent
{
    Q_OBJECT

public:
    explicit ToolsSidebar(QWidget *parent = nullptr);
    void setupSidebar() override;
};

#endif
