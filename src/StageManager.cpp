#include "StageManager.h"
#include "AEDController.h" // forward declaration

StageManager::StageManager(Stage s, AEDController* controller, QObject* parent)
    : QObject(parent), stage(s), controller(controller) {
    
    screen = controller->getScreen(); // Pass in the screen from the controller
    status = 0; // set to Idle state for each stage
}

bool StageManager::isDone() const{
    return status == 0;
}

bool StageManager::isActive() const{
    return status > 0; // All normal status codes > 0
}

bool StageManager::isIdle() const{
    return status == -1;
}

bool StageManager::isError() const{
    return status < -1; // All error states have value less than -1
}


bool StageManager::setStatus(int s){
    status = s;
    return true;
}

int StageManager::getStatusCode() const{
    return status;
}