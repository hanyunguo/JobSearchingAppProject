#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>

#include "DailyPlannerPage.h"
#include "DailyPlannerPageSidebarFactory.h"

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

    // Main content area
    dailyPlannerComponent = new DailyPlannerComponent(this);
    dailyPlannerComponent->setDate(QDate::currentDate());

    // connect(dailyPlannerComponent, &DailyPlannerComponent::timeSlotClicked, this, &DailyPlannerPage::handleTimeslotClicked);

    // Layout
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(sidebar);
    layout->addWidget(dailyPlannerComponent);

    setLayout(layout);
}

void DailyPlannerPage::handleNavigation(const QString &pageName)
{
    emit changePageRequested(pageName);
}

void DailyPlannerPage::handleDateChange(const QDate &date)
{
    dailyPlannerComponent->setDate(date);
}

void DailyPlannerPage::changeToTargetDate(const QDate &date){
    this->dailyPlannerComponent->setDate(date);
    this->dailyPlannerComponent->loadSchedules();
}
