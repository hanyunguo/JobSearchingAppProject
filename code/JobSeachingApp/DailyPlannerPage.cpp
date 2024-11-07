#include <QHBoxLayout>
#include <QLabel>
#include <QDialog>

#include "DailyPlannerPage.h"
#include "DailyPlannerPageSidebarFactory.h"
#include "AddScheduleComponent.h"

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

    // Corrected connect statement
    connect(dailyPlannerComponent, &DailyPlannerComponent::timeSlotClicked, this, &DailyPlannerPage::handleTimeslotClicked);

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

void DailyPlannerPage::handleTimeslotClicked(int hour)
{
    AddScheduleComponent *addScheduleComponent = new AddScheduleComponent(dailyPlannerComponent->getDate(), hour, this);

    connect(addScheduleComponent, &AddScheduleComponent::scheduleUpdated, this, &DailyPlannerPage::refreshSchedules);

    // Display the AddScheduleComponent in a modal dialog
    QDialog *dialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(addScheduleComponent);
    dialog->setLayout(layout);
    dialog->exec();
}

void DailyPlannerPage::refreshSchedules()
{
    dailyPlannerComponent->updateSchedules();
}

void DailyPlannerPage::changeToTargetDate(const QDate &date){
    this->dailyPlannerComponent->setDate(date);
    this->dailyPlannerComponent->loadSchedules();
}
