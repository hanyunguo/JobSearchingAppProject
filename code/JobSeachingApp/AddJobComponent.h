#ifndef ADDJOBCOMPONENT_H
#define ADDJOBCOMPONENT_H

#include <QWidget>
#include "Job.h"
#include "XMLManager.h"

class QLineEdit;
class QPushButton;

class AddJobComponent : public QWidget
{
    Q_OBJECT
public:
    explicit AddJobComponent(QWidget *parent = nullptr);
    void addJob(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription);
signals:
    void jobUpdated();
    void closePopUp();

private slots:
    void onSaveClicked();

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
};

#endif // ADDJOBCOMPONENT_H
