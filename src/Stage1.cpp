#include "Stage1.h"
#include "AEDController.h" // Forward declare

Stage1::Stage1(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POWER, controller, parent) {

}

bool Stage1::setStatus(Stage1Power s){ // @ Overload from StageManger
    // status = static_cast<int>(s);
    status = s;
    return true;
}

bool Stage1::activate(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}

bool Stage1::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}