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

    calendarViewComponent = new CalendarViewComponent(this);
    connect(calendarViewComponent, &CalendarViewComponent::dateSelected, this, &CalendarPage::handleDateSelected);

    // Main content area
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(calendarViewComponent);

    setLayout(layout);
}

void CalendarPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}

void CalendarPage::handleDateSelected(const QDate &date)
{
    emit targetPageRequested(date);
}
