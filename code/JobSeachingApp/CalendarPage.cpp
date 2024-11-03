#include "CalendarPage.h"
#include "CalendarPageSidebarFactory.h"
#include <QHBoxLayout>
#include <QLabel>

CalendarPage::CalendarPage(QWidget *parent)
    : Page(parent)
{
    setupPage();
}

void CalendarPage::setupPage()
{
    // Create sidebar using factory
    CalendarPageSidebarFactory factory;
    sidebar = factory.createSidebar(this);

    connect(sidebar, &SidebarComponent::navigationRequested, this, &CalendarPage::handleNavigation);

    // Main content area
    QLabel *content = new QLabel("Calendar Content", this);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(content);

    setLayout(layout);
}

void CalendarPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}
