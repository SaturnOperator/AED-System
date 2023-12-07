#include "Stage1.h"
#include "AEDController.h" // Forward declare

Stage1::Stage1(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POWER, controller, parent) {

}

bool Stage1::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    // Code here

    return true;
}

void Stage1::stop(){
    // Code here
}

bool Stage1::setStatus(Stage1Power s){ // @ Overload from StageManger
    // status = static_cast<int>(s);
    status = s;
    return true;
}

bool Stage1::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}