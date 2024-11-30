#include "AddJobCommand.h"

AddJobCommand::AddJobCommand(Job job) {
    this->job.setJobTitle(job.getJobTitle());
    this->job.setApplicationLink(job.getApplicationLink());
    this->job.setCompanyName(job.getCompanyName());
    this->job.setJobDescription(job.getJobDescription());

}

bool AddJobCommand::execute(){
    // Save the job using XMLManager
    return XMLManager::getInstance().saveJobXML(job);
}
