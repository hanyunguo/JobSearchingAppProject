#ifndef JOBAPPLICATIONPAGE_H
#define JOBAPPLICATIONPAGE_H

#include "Page.h"
#include "SidebarComponent.h"
#include "JobListComponent.h"

class JobApplicationPage : public Page
{
    Q_OBJECT

public:
    explicit JobApplicationPage(QWidget *parent = nullptr);
    void setupPage() override;

private slots:
    void handleNavigation(const QString &pageName);
    void refreshJobPage();

private:
    SidebarComponent *sidebar;
    JobListComponent* jobListComponent;
};

#endif // JOBAPPLICATIONPAGE_H
