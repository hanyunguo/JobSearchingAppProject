#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DailyPlannerPage.h"
#include "CalendarPage.h"
#include "TaskPage.h"
#include "JobApplicationPage.h"
#include <QStackedWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // Create pages
    dailyPlannerPage = new DailyPlannerPage(this);
    calendarPage = new CalendarPage(this);
    taskPage = new TaskPage(this);
    jobApplicationPage = new JobApplicationPage(this);

    // Add pages to stacked widget
    stackedWidget->addWidget(dailyPlannerPage);
    stackedWidget->addWidget(calendarPage);
    stackedWidget->addWidget(taskPage);
    stackedWidget->addWidget(jobApplicationPage);

    // Connect page signals to MainWindow slot
    connect(dailyPlannerPage, &Page::changePageRequested, this, &MainWindow::changePage);
    connect(calendarPage, &Page::changePageRequested, this, &MainWindow::changePage);
    connect(taskPage, &Page::changePageRequested, this, &MainWindow::changePage);
    connect(jobApplicationPage, &Page::changePageRequested, this, &MainWindow::changePage);

    // Set initial page
    stackedWidget->setCurrentWidget(dailyPlannerPage);
}

MainWindow::~MainWindow()
{
}


void MainWindow::changePage(const QString &pageName)
{
    if (pageName == "DailyPlannerPage")
    {
        stackedWidget->setCurrentWidget(dailyPlannerPage);
    }
    else if (pageName == "CalendarPage")
    {
        stackedWidget->setCurrentWidget(calendarPage);
    }
    else if (pageName == "TaskPage")
    {
        stackedWidget->setCurrentWidget(taskPage);
    }
    else if (pageName == "JobApplicationPage")
    {
        stackedWidget->setCurrentWidget(jobApplicationPage);
    }
}
