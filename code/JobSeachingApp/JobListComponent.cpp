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
    addJobButton->setStyleSheet("QPushButton {"
                                "background-color: #4CAF50;"
                                "color: white;"
                                "font-size: 14px;"
                                "border-radius: 5px;"
                                "padding: 10px;"
                                "}");
    addJobButton->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(addJobButton, Qt::AlignTop, Qt::AlignRight);
    mainLayout->setSpacing(10);

    // Connect the button to the slot
    connect(addJobButton, &QPushButton::clicked, this, &JobListComponent::onAddJobClicked);

    // Initialize jobTable as a member variable
    jobTable = new QTableWidget(this);
    jobTable->setColumnCount(6);
    jobTable->setHorizontalHeaderLabels({"Job Title", "Company Name", "Application Link", "Job Description", "  ", "    "});

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

        // Create the Edit button
        QPushButton *editButton = new QPushButton("Edit", this);
        editButton->setFixedSize(80, 30);   // Set the size of the Edit button
        editButton->setStyleSheet("QPushButton {"
                                  "background-color: #A8E6CF;"  // Light Pastel Green (for Edit)
                                  "color: #424242;"  // Dark Gray text for contrast
                                  "font-size: 12px;"
                                  "font-weight: normal;"
                                  "border-radius: 5px;"
                                  "padding: 6px 14px;"
                                  "border: 1px solid #A8E6CF;"  // Matching border color
                                  "}");
        editButton->setStyleSheet("QPushButton:hover {"
                                  "background-color: #81C8A5;"  // Darker mint (for hover effect)
                                  "}");

        // Create the Delete button
        QPushButton *deleteButton = new QPushButton("Delete", this);
        deleteButton->setFixedSize(80, 30);
        deleteButton->setStyleSheet("QPushButton {"
                                    "background-color: #FFCDD2;"  // Soft Blush Pink (for Delete)
                                    "color: #424242;"  // Dark Gray text for contrast
                                    "font-size: 12px;"
                                    "font-weight: normal;"
                                    "border-radius: 5px;"
                                    "padding: 6px 14px;"
                                    "border: 1px solid #FFCDD2;"  // Matching border color
                                    "}");
        deleteButton->setStyleSheet("QPushButton:hover {"
                                    "background-color: #FFABAB;"  // Soft peach (for hover effect)
                                    "}");

        // Connect buttons to their respective actions
        connect(editButton, &QPushButton::clicked, this, [this, job]() { onEditJobClicked(job); });
        connect(deleteButton, &QPushButton::clicked, this, [this, job]() { onDeleteJobClicked(job); });

        // Add buttons to their respective columns
        jobTable->setCellWidget(row, 4, editButton);  // Edit button in 5th column
        jobTable->setCellWidget(row, 5, deleteButton);  // Delete button in 6th column


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

void JobListComponent::onEditJobClicked(const Job &oldJob)
{
    // Create a new dialog to edit job details
    QDialog *editDialog = new QDialog(this);
    editDialog->setWindowTitle("Edit Job");

    QVBoxLayout *layout = new QVBoxLayout(editDialog);

    // Create form fields with current job details
    QLineEdit *titleEdit = new QLineEdit(QString::fromStdString(oldJob.getJobTitle()), editDialog);
    QLineEdit *companyEdit = new QLineEdit(QString::fromStdString(oldJob.getCompanyName()), editDialog);
    QLineEdit *linkEdit = new QLineEdit(QString::fromStdString(oldJob.getApplicationLink()), editDialog);
    QLineEdit *descriptionEdit = new QLineEdit(QString::fromStdString(oldJob.getJobDescription()), editDialog);

    layout->addWidget(new QLabel("Job Title:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Company Name:"));
    layout->addWidget(companyEdit);
    layout->addWidget(new QLabel("Application Link:"));
    layout->addWidget(linkEdit);
    layout->addWidget(new QLabel("Job Description:"));
    layout->addWidget(descriptionEdit);

    // Save button to update the job information
    QPushButton *saveButton = new QPushButton("Save", editDialog);
    layout->addWidget(saveButton);

    // When save is clicked, update the job and refresh the list
    connect(saveButton, &QPushButton::clicked, this, [this, titleEdit, companyEdit, linkEdit, descriptionEdit, oldJob, editDialog]() {
        // Create an updated job object with new details from the form
        Job updatedJob(titleEdit->text().toStdString(),
                       companyEdit->text().toStdString(),
                       linkEdit->text().toStdString(),
                       descriptionEdit->text().toStdString());

        // Pass both oldJob and updatedJob to the XMLManager for editing
        XMLManager::getInstance().editJobXML(oldJob, updatedJob);

        // Refresh the job list
        updateJobList();

        // Close the edit dialog
        editDialog->accept();
    });

    // Execute the dialog
    editDialog->exec();
}

void JobListComponent::onDeleteJobClicked(const Job &job)
{
    // Create a custom dialog for the delete confirmation
    QDialog *deleteDialog = new QDialog(this);
    deleteDialog->setWindowTitle("Delete Job");

    // Set dialog layout
    QVBoxLayout *layout = new QVBoxLayout(deleteDialog);

    // Add message text
    QLabel *messageLabel = new QLabel("Are you sure you want to delete this job?", deleteDialog);
    layout->addWidget(messageLabel);

    // Create Yes and No buttons
    QPushButton *yesButton = new QPushButton("Yes", deleteDialog);
    QPushButton *noButton = new QPushButton("No", deleteDialog);

    // Apply button styles with significantly larger sizes
    QString yesButtonStyle = "QPushButton {"
                             "background-color: #A8E6CF;"  // Light Pastel Green (for Edit)
                             "color: #424242;"  // Dark Gray text for contrast
                             "font-size: 16px;"  // Slightly smaller font size
                             "font-weight: bold;"  // Bold text for better visibility
                             "border-radius: 8px;"  // Rounded corners
                             "padding: 10px 20px;"  // Reduced padding for more moderate size
                             "}";

    QString noButtonStyle = "QPushButton {"
                            "background-color: #FFCDD2;"  // Soft Blush Pink (for Delete)
                            "color: #424242;"  // Dark Gray text for contrast
                            "font-size: 16px;"  // Slightly smaller font size
                            "font-weight: bold;"  // Bold text for better visibility
                            "border-radius: 8px;"  // Rounded corners
                            "padding: 10px 20px;"  // Reduced padding for more moderate size
                            "}";

    yesButton->setStyleSheet(yesButtonStyle);
    noButton->setStyleSheet(noButtonStyle);

    // Create a button layout and add buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(yesButton);
    buttonLayout->addWidget(noButton);
    layout->addLayout(buttonLayout);

    // Center the buttons in the dialog
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Adjust margins for spacing around the buttons
    layout->setContentsMargins(50, 20, 50, 20);  // Added top and bottom margins

    // Connect buttons to actions
    connect(yesButton, &QPushButton::clicked, this, [this, job, deleteDialog]() {
        // Perform the deletion (remove from list, update XML, etc.)
        XMLManager::getInstance().deleteJobXML(job);
        updateJobList(); // Refresh the job list after deletion
        deleteDialog->accept();  // Close the dialog
    });

    connect(noButton, &QPushButton::clicked, deleteDialog, &QDialog::reject);  // Close the dialog on "No"

    // Execute the dialog
    deleteDialog->exec();
}
