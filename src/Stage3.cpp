#include "Stage3.h"
#include "AEDController.h" // Forward declare

Stage3::Stage3(AEDController* controller, QObject* parent) : 
    StageManager(Stage::ANALYZE, controller, parent) {

}

bool Stage3::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    // Code here

    return true;
}

void Stage3::stop(){
    // Code here
}

bool Stage3::setStatus(Stage3Analyze s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage3::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}