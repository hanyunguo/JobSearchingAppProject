#ifndef ADDTASKCOMMAND_H
#define ADDTASKCOMMAND_H

#include "Command.h"
#include "Task.h"
#include "XMLManager.h"

class AddTaskCommand : public Command
{
public:
    AddTaskCommand(Task *task);
    bool execute() override;
private:
    Task* task;
};

#endif // ADDTASKCOMMAND_H
