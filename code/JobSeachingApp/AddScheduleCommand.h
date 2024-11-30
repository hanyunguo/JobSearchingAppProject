#ifndef ADDSCHEDULECOMMAND_H
#define ADDSCHEDULECOMMAND_H

#include "Command.h"
#include "Schedule.h".h"
#include "XMLManager.h"

class AddScheduleCommand  : public Command
{
public:
    AddScheduleCommand(Schedule schedule);
    bool execute() override;
private:
    Schedule schedule;
};

#endif // ADDSCHEDULECOMMAND_H
