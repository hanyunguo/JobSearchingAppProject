#ifndef JOBLISTCOMPONENT_H
#define JOBLISTCOMPONENT_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <vector>

#include "Job.h"

class JobListComponent : public QWidget
{
    Q_OBJECT

public:
    explicit JobListComponent(QWidget *parent = nullptr);

public slots:
    void onAddJobClicked();
    void updateJobList();

private:
    void setupUI();

    QTableWidget *jobTable;
    QPushButton *addJobButton;
    std::vector<Job> jobList;
};

#endif // JOBLISTCOMPONENT_H
