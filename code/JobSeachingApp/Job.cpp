#include "Job.h"

Job::Job()
{
}

Job::Job(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription)
    : jobTitle(jobTitle), companyName(companyName), applicationLink(applicationLink), jobDescription(jobDescription)
{
}

// Getters
std::string Job::getJobTitle() const { return jobTitle; }
std::string Job::getCompanyName() const { return companyName; }
std::string Job::getApplicationLink() const { return applicationLink; }
std::string Job::getJobDescription() const { return jobDescription; }

// Setters
void Job::setJobTitle(const std::string &jobTitle) { this->jobTitle = jobTitle; }
void Job::setCompanyName(const std::string &companyName) { this->companyName = companyName; }
void Job::setApplicationLink(const std::string &applicationLink) { this->applicationLink = applicationLink; }
void Job::setJobDescription(const std::string &jobDescription) { this->jobDescription = jobDescription; }
