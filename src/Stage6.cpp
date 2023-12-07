#include "Stage6.h"
#include "AEDController.h" // Forward declare

Stage6::Stage6(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POST_USE, controller, parent) {

}

bool Stage6::setStatus(Stage6PostUse s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage6::activate(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}

bool Stage6::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}