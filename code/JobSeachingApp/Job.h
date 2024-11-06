#ifndef JOB_H
#define JOB_H

#include <string>

class Job
{
public:
    Job();
    Job(const std::string &jobTitle, const std::string &companyName, const std::string &applicationLink, const std::string &jobDescription);

    // Getters
    std::string getJobTitle() const;
    std::string getCompanyName() const;
    std::string getApplicationLink() const;
    std::string getJobDescription() const;

    // Setters
    void setJobTitle(const std::string &jobTitle);
    void setCompanyName(const std::string &companyName);
    void setApplicationLink(const std::string &applicationLink);
    void setJobDescription(const std::string &jobDescription);

private:
    std::string jobTitle;
    std::string companyName;
    std::string applicationLink;
    std::string jobDescription;
};

#endif // JOB_H
