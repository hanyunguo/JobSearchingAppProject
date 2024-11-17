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

    taskListComponent = new TaskListComponent(this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(taskListComponent);

    setLayout(layout);
}

void TaskPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}

void TaskPage::refreshJobPage()
{
    taskListComponent->updateTaskList();
}

