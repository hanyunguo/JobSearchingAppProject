#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "Page.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changePage(const QString &pageName);
    void changeToTarget(const QDate &date);

private:
    QStackedWidget *stackedWidget;
    Page *dailyPlannerPage;
    Page *calendarPage;
    Page *taskPage;
    Page *jobApplicationPage;
    Page *targetDailyPlannerPage;
};
#endif
