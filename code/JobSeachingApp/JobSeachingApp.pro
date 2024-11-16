QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AddJobComponent.cpp \
    AddScheduleComponent.cpp \
    CalendarPage.cpp \
    CalendarPageSidebar.cpp \
    CalendarPageSidebarFactory.cpp \
    CalendarViewComponent.cpp \
    DailyPlannerComponent.cpp \
    DailyPlannerPage.cpp \
    DailyPlannerPageSidebar.cpp \
    DailyPlannerPageSidebarFactory.cpp \
    Job.cpp \
    JobApplicationPage.cpp \
    JobListComponent.cpp \
    Page.cpp \
    Schedule.cpp \
    SidebarComponent.cpp \
    Task.cpp \
    TaskPage.cpp \
    ToolsSidebar.cpp \
    ToolsSidebarFactory.cpp \
    XMLManager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    AddJobComponent.h \
    AddScheduleComponent.h \
    CalendarPage.h \
    CalendarPageSidebar.h \
    CalendarPageSidebarFactory.h \
    CalendarViewComponent.h \
    DailyPlannerComponent.h \
    DailyPlannerPage.h \
    DailyPlannerPageSidebar.h \
    DailyPlannerPageSidebarFactory.h \
    Job.h \
    JobApplicationPage.h \
    JobListComponent.h \
    Page.h \
    Schedule.h \
    SidebarComponent.h \
    SidebarComponentFactory.h \
    Task.h \
    TaskPage.h \
    ToolsSidebar.h \
    ToolsSidebarFactory.h \
    XMLManager.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
