#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

#include "AddJobComponent.h"

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
    jobTitleLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");  // Label style
    mainLayout->addWidget(jobTitleLabel);

    jobTitleEdit = new QLineEdit(this);
    jobTitleEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(jobTitleEdit);

    // Company Name
    QLabel *companyNameLabel = new QLabel("Company Name:", this);
    companyNameLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(companyNameLabel);

    companyNameEdit = new QLineEdit(this);
    companyNameEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(companyNameEdit);

    // Application Link
    QLabel *applicationLinkLabel = new QLabel("Application Link:", this);
    applicationLinkLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(applicationLinkLabel);

    applicationLinkEdit = new QLineEdit(this);
    applicationLinkEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(applicationLinkEdit);

    // Job Description
    QLabel *jobDescriptionLabel = new QLabel("Job Description:", this);
    jobDescriptionLabel->setStyleSheet("color: #333333; font-size: 14px; font-weight: bold;");
    mainLayout->addWidget(jobDescriptionLabel);

    jobDescriptionEdit = new QLineEdit(this);
    jobDescriptionEdit->setStyleSheet("background-color: #F2F2F2; color: #333333; border: 1px solid #B0B0B0; border-radius: 5px; padding: 8px;");
    mainLayout->addWidget(jobDescriptionEdit);

    // Buttons Layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("background-color: #B0B0B0; color: white; border-radius: 5px; padding: 8px 15px; font-size: 14px;");
    saveButton->setFixedWidth(100);  // Fixed width for consistency
    buttonLayout->addWidget(saveButton);

    // Add button layout to the main layout
    mainLayout->addLayout(buttonLayout);

    // Set the layout for the component
    setLayout(mainLayout);
}

void AddJobComponent::connectSignals()
{
    connect(saveButton, &QPushButton::clicked, this, &AddJobComponent::onSaveClicked);
}


bool AddJobComponent::addJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription)
{
    Job job(jobTitle, companyName, applicationLink, jobDescription);
    // Save the Job using XMLManager
    bool addResult = XMLManager::getInstance()->saveJobXML(job);

    // Update the current job
    currentJob = job;

    // Emit the signal to notify that the job has been updated
    emit jobUpdated();
    return addResult;
}

void AddJobComponent::onSaveClicked(){
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

    // Close the component if necessary
    emit closePopUp();
}
