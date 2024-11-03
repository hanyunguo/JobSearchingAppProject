#ifndef TASKPAGE_H
#define TASKPAGE_H

#include "Page.h"
#include "SidebarComponent.h"

class TaskPage : public Page
{
    Q_OBJECT

public:
    explicit TaskPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
};

#endif // TASKPAGE_H
