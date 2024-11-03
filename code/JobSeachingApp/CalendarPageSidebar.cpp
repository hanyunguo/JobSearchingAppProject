#include "CalendarPageSidebar.h"
#include <QPushButton>
#include <QVBoxLayout>

CalendarPageSidebar::CalendarPageSidebar(QWidget *parent)
    : SidebarComponent(parent)
{
    setupSidebar();
}

void CalendarPageSidebar::setupSidebar()
{
    QPushButton *dailyPlannerButton = new QPushButton("Daily Planner Page", this);
    QPushButton *taskButton = new QPushButton("Task Page", this);
    QPushButton *jobAppButton = new QPushButton("Job Application Page", this);

    connect(dailyPlannerButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("DailyPlannerPage");
    });
    connect(taskButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("TaskPage");
    });
    connect(jobAppButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("JobApplicationPage");
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dailyPlannerButton);
    layout->addWidget(taskButton);
    layout->addWidget(jobAppButton);
    layout->addStretch();

    setLayout(layout);
}
