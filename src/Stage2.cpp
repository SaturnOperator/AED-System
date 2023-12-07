#include "Stage2.h"
#include "AEDController.h" // Forward declare

Stage2::Stage2(AEDController* controller, QObject* parent) : 
    StageManager(Stage::PADS, controller, parent) {

}

bool Stage2::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    // Code here

    return true;
}

void Stage2::stop(){
    // Code here
}

bool Stage2::setStatus(Stage2Install s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}


bool Stage2::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}