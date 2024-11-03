#include "DailyPlannerPage.h"
#include "DailyPlannerPageSidebarFactory.h"
#include <QHBoxLayout>
#include <QLabel>

DailyPlannerPage::DailyPlannerPage(QWidget *parent)
    : Page(parent)
{
    setupPage();
}

void DailyPlannerPage::setupPage()
{
    // Create sidebar using factory
    DailyPlannerPageSidebarFactory factory;
    sidebar = factory.createSidebar(this);

    connect(sidebar, &SidebarComponent::navigationRequested, this, &DailyPlannerPage::handleNavigation);

    // Main content area (replace QLabel with actual content)
    QLabel *content = new QLabel("Daily Planner Content", this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(content);

    setLayout(layout);
}

void DailyPlannerPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}
