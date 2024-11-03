#include "ToolsSidebar.h"
#include <QPushButton>
#include <QVBoxLayout>

ToolsSidebar::ToolsSidebar(QWidget *parent)
    : SidebarComponent(parent)
{
    setupSidebar();
}

void ToolsSidebar::setupSidebar()
{
    QPushButton *dailyPlannerButton = new QPushButton("Daily Planner Page", this);

    connect(dailyPlannerButton, &QPushButton::clicked, [this]() {
        emit navigationRequested("DailyPlannerPage");
    });

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(dailyPlannerButton);
    layout->addStretch();

    setLayout(layout);
}
