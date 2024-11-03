#ifndef JOBAPPLICATIONPAGE_H
#define JOBAPPLICATIONPAGE_H

#include "Page.h"
#include "SidebarComponent.h"

class JobApplicationPage : public Page
{
    Q_OBJECT

public:
    explicit JobApplicationPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
};

#endif // JOBAPPLICATIONPAGE_H
