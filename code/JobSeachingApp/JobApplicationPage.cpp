#include "JobApplicationPage.h"
#include "ToolsSidebarFactory.h"
#include <QHBoxLayout>
#include <QLabel>

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
    QLabel *content = new QLabel("Job Application Content", this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(content);

    setLayout(layout);
}

void JobApplicationPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}
