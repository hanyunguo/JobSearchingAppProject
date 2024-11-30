#ifndef ADDJOBCOMMAND_H
#define ADDJOBCOMMAND_H

#include "Command.h"
#include "Job.h"
#include "XMLManager.h"

class AddJobCommand : public Command
{
public:
    AddJobCommand(Job job);
    bool execute() override;
private:
    Job job;
};

#endif // ADDJOBCOMMAND_H
