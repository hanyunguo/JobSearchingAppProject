#include "AddTaskCommand.h"

AddTaskCommand::AddTaskCommand(Task* task) {
    this->task = task;
}

bool AddTaskCommand::execute(){
    // Save the job using XMLManager
    return XMLManager::getInstance().saveTaskXML(task);
}
