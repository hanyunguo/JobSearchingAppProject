#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableWidgetItem>

#include "JobListComponent.h"
#include "XMLManager.h"
#include "AddJobComponent.h"

JobListComponent::JobListComponent(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    updateJobList(); // Initially load the job list
}

void JobListComponent::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Button to add new job
    addJobButton = new QPushButton("Add New Job Application", this);
    mainLayout->addWidget(addJobButton, Qt::AlignTop, Qt::AlignRight);
    mainLayout->setSpacing(10);

    // Connect the button to the slot
    connect(addJobButton, &QPushButton::clicked, this, &JobListComponent::onAddJobClicked);

    // Initialize jobTable as a member variable
    jobTable = new QTableWidget(this);
    jobTable->setColumnCount(4);
    jobTable->setHorizontalHeaderLabels({"Job Title", "Company Name", "Application Link", "Job Description"});

    jobTable->setEditTriggers(QAbstractItemView::NoEditTriggers); // Disable direct editing
    mainLayout->addWidget(jobTable);

    setLayout(mainLayout);
}

void JobListComponent::updateJobList()
{
    jobTable->setRowCount(0); // Clear existing table data

    jobList = XMLManager::getInstance().readJobXML();

    int row = 0;
    for (const Job &job : jobList)
    {
        jobTable->insertRow(row);

        // Create items for each cell
        QTableWidgetItem *titleItem = new QTableWidgetItem(QString::fromStdString(job.getJobTitle()));
        QTableWidgetItem *companyItem = new QTableWidgetItem(QString::fromStdString(job.getCompanyName()));
        QTableWidgetItem *linkItem = new QTableWidgetItem(QString::fromStdString(job.getApplicationLink()));
        QTableWidgetItem *descriptionItem = new QTableWidgetItem(QString::fromStdString(job.getJobDescription()));

        jobTable->setItem(row, 0, titleItem);
        jobTable->setItem(row, 1, companyItem);
        jobTable->setItem(row, 2, linkItem);
        jobTable->setItem(row, 3, descriptionItem);

        row++;
    }

    // Resize columns to fit content
    jobTable->resizeColumnsToContents();
}

void JobListComponent::onAddJobClicked()
{
    // Create an instance of AddJobComponent
    AddJobComponent *addJobDialog = new AddJobComponent(this);
    QDialog *dialog = new QDialog(this);

    // Connect the jobUpdated signal to update the job list after the job is added
    connect(addJobDialog, &AddJobComponent::jobUpdated, this, &JobListComponent::updateJobList);
    connect(addJobDialog, &AddJobComponent::closePopUp, dialog, &QDialog::accept);

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(addJobDialog);
    dialog->setLayout(layout);
    dialog->exec();
}
