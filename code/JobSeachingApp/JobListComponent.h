#ifndef JOBLISTCOMPONENT_H
#define JOBLISTCOMPONENT_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <vector>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDateTime>

#include "Job.h"

class JobListComponent : public QWidget
{
    Q_OBJECT

public:
    explicit JobListComponent(QWidget *parent = nullptr);

public slots:
    void onAddJobClicked();
    void updateJobList();
    void onEditJobClicked(const Job &job);
    void onDeleteJobClicked(const Job &job);

private:
    void setupUI();

    QTableWidget *jobTable;
    QPushButton *addJobButton;
    std::vector<Job> jobList;
};

#endif // JOBLISTCOMPONENT_H
