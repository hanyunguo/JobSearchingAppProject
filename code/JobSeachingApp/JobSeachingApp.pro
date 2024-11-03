QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CalendarPage.cpp \
    CalendarPageSidebar.cpp \
    CalendarPageSidebarFactory.cpp \
    DailyPlannerPage.cpp \
    DailyPlannerPageSidebar.cpp \
    DailyPlannerPageSidebarFactory.cpp \
    JobApplicationPage.cpp \
    Page.cpp \
    SidebarComponent.cpp \
    TaskPage.cpp \
    ToolsSidebar.cpp \
    ToolsSidebarFactory.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CalendarPage.h \
    CalendarPageSidebar.h \
    CalendarPageSidebarFactory.h \
    DailyPlannerPage.h \
    DailyPlannerPageSidebar.h \
    DailyPlannerPageSidebarFactory.h \
    JobApplicationPage.h \
    Page.h \
    SidebarComponent.h \
    SidebarComponentFactory.h \
    TaskPage.h \
    ToolsSidebar.h \
    ToolsSidebarFactory.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
