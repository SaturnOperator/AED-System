#include "Stage2.h"
#include "AEDController.h" // Forward declare

Stage2::Stage2(AEDController* controller, QObject* parent) : 
    StageManager(Stage::PADS, controller, parent) {

}

bool Stage2::setStatus(Stage2Install s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage2::activate(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}

bool Stage2::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}