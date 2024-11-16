#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>

#include "JobApplicationPage.h"
#include "ToolsSidebarFactory.h"
#include "JobListComponent.h"

JobApplicationPage::JobApplicationPage(QWidget *parent)
    : Page(parent)
{
    setupPage();
}

void JobApplicationPage::setupPage()
{
    // Create sidebar using factory
    ToolsSidebarFactory factory;
    sidebar = factory.createSidebar(this);

    connect(sidebar, &SidebarComponent::navigationRequested, this, &JobApplicationPage::handleNavigation);

    // Main content area
    jobListComponent = new JobListComponent(this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(jobListComponent);

    setLayout(layout);
}

void JobApplicationPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}

void JobApplicationPage::refreshJobPage()
{
    jobListComponent->updateJobList();
}
