#include "TaskPage.h"
#include "ToolsSidebarFactory.h"
#include <QHBoxLayout>
#include <QLabel>

TaskPage::TaskPage(QWidget *parent)
    : Page(parent)
{
    setupPage();
}

void TaskPage::setupPage()
{
    // Create sidebar using factory
    ToolsSidebarFactory factory;
    sidebar = factory.createSidebar(this);

    connect(sidebar, &SidebarComponent::navigationRequested, this, &TaskPage::handleNavigation);

    // Main content area
    QLabel *content = new QLabel("Task Content", this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(content);

    setLayout(layout);
}

void TaskPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}
