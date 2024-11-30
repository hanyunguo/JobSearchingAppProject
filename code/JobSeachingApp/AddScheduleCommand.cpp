#include "AddScheduleCommand.h"

AddScheduleCommand::AddScheduleCommand(Schedule schedule) {
    this->schedule.setTimeslot(schedule.getTimeslot());
    this->schedule.setTask(schedule.getTask());
    this->schedule.setDescription(schedule.getDescription());
    this->schedule.setCompleted(schedule.isCompleted());
}

bool AddScheduleCommand::execute(){
    // Save the schedule using XMLManager
    return XMLManager::getInstance().saveScheduleXML(schedule);
}
