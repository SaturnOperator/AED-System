#include "Stage5.h"
#include "AEDController.h" // Forward declare

Stage5::Stage5(AEDController* controller, QObject* parent) : 
    StageManager(Stage::CPR, controller, parent) {

        
    
}

bool Stage5::setStatus(Stage5CPR s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage5::activate(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one
    screen->startCountdown();
    return true;
}

bool Stage5::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one
    screen->startCountdown();
    return true;
}