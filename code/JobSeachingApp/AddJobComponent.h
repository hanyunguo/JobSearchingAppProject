#ifndef ADDJOBCOMPONENT_H
#define ADDJOBCOMPONENT_H

#include <QWidget>
#include "Job.h"

class QLineEdit;
class QPushButton;

class AddJobComponent : public QWidget
{
    Q_OBJECT
public:
    explicit AddJobComponent(QWidget *parent = nullptr);
    void addJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription);
    void editJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription);
    void deleteJob(const Job &job);

signals:
    void jobUpdated();
    void closePopUp();

private slots:
    void onSaveClicked();
    void onDeleteClicked();

private:
    void setupUI();
    void connectSignals();

    // UI elements
    QLineEdit *jobTitleEdit;
    QLineEdit *companyNameEdit;
    QLineEdit *applicationLinkEdit;
    QLineEdit *jobDescriptionEdit;

    // Member variables
    Job currentJob;
    int hour;

    QPushButton *saveButton;
    QPushButton *deleteButton;
};

#endif // ADDJOBCOMPONENT_H
