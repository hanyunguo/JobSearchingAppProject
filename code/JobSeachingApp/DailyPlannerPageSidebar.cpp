#include "DailyPlannerPageSidebar.h"
#include <QPushButton>
#include <QVBoxLayout>

DailyPlannerPageSidebar::DailyPlannerPageSidebar(QWidget *parent)
    : SidebarComponent(parent)
{
    setupSidebar();
}

void DailyPlannerPageSidebar::setupSidebar()
{
    QPushButton *calendarButton = new QPushButton("Calendar Page", this);
    QPushButton *taskButton = new QPushButton("Task Page", this);
    QPushButton *jobAppButton = new QPushButton("Job Application Page", this);

    connect(calendarButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("CalendarPage");
    });
    connect(taskButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("TaskPage");
    });
    connect(jobAppButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("JobApplicationPage");
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(calendarButton);
    layout->addWidget(taskButton);
    layout->addWidget(jobAppButton);
    layout->addStretch();

    setLayout(layout);
}
