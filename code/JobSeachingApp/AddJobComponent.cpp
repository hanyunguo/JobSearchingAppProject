#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "AddJobComponent.h"
#include "XMLManager.h"
AddJobComponent::AddJobComponent(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    connectSignals();
}

void AddJobComponent::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Job Title
    QLabel *jobTitleLabel = new QLabel("Job Title:", this);
    mainLayout->addWidget(jobTitleLabel);

    jobTitleEdit = new QLineEdit(this);
    mainLayout->addWidget(jobTitleEdit);

    // Company Name
    QLabel *companyNameLabel = new QLabel("Company Name:", this);
    mainLayout->addWidget(companyNameLabel);

    companyNameEdit = new QLineEdit(this);
    mainLayout->addWidget(companyNameEdit);

    // Application Link
    QLabel *applicationLinkLabel = new QLabel("Application Link:", this);
    mainLayout->addWidget(applicationLinkLabel);

    applicationLinkEdit = new QLineEdit(this);
    mainLayout->addWidget(applicationLinkEdit);

    // Job Description
    QLabel *jobDescriptionLabel = new QLabel("Job Description:", this);
    mainLayout->addWidget(jobDescriptionLabel);

    jobDescriptionEdit = new QLineEdit(this);
    mainLayout->addWidget(jobDescriptionEdit);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save", this);
    buttonLayout->addWidget(saveButton);

    deleteButton = new QPushButton("Delete", this);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

void AddJobComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddJobComponent::onSaveClicked);
    connect(deleteButton, &QPushButton::clicked, this, &AddJobComponent::onDeleteClicked);
}


void AddJobComponent::addJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription)
{
    Job job(jobTitle, companyName, applicationLink, jobDescription);
    // Save the job using XMLManager
    XMLManager::getInstance().saveJobXML(job);

    // Update the current job
    currentJob = job;

    // Emit the signal to notify that the job has been updated
    emit jobUpdated();
}

void AddJobComponent::editJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription)
{
    // Update the current job
    currentJob.setJobTitle(jobTitle);
    currentJob.setCompanyName(companyName);
    currentJob.setApplicationLink(applicationLink);
    currentJob.setJobDescription(jobDescription);

    // Save the updated job using XMLManager
    XMLManager::getInstance().saveJobXML(currentJob);

    // Emit the signal to notify that the job has been updated
    emit jobUpdated();
}

void AddJobComponent::deleteJob(const Job &job)
{
    // Delete the job using XMLManager
    // XMLManager::getInstance().deleteJobXML(job);

    // Clear the current job
    currentJob = Job();

    // Emit the signal to notify that the job has been updated
    emit jobUpdated();

    close();
}

void AddJobComponent::onSaveClicked()
{
    // Get input values from UI elements
    QString jobTitle = jobTitleEdit->text();
    QString companyName = companyNameEdit->text();
    QString applicationLink = applicationLinkEdit->text();
    QString jobDescription = jobDescriptionEdit->text();

    if (currentJob.getJobTitle().empty())
    {
        // Adding a new job
        addJob(jobTitle.toStdString(), companyName.toStdString(), applicationLink.toStdString(), jobDescription.toStdString());
    }
    else
    {
        // Editing an existing job
        editJob(jobTitle.toStdString(), companyName.toStdString(), applicationLink.toStdString(), jobDescription.toStdString());
    }

    // Close the component if necessary
    emit closePopUp();
}

void AddJobComponent::onDeleteClicked()
{
    if (!currentJob.getJobTitle().empty())
    {
        // Delete the current job
        // deleteJob(currentJob);
    }

    // Close the component if necessary
    emit closePopUp();
}
