#include "Stage6.h"
#include "AEDController.h" // Forward declare

Stage6::Stage6(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POST_USE, controller, parent) {

    setStatus(Stage6PostUse::INIT);
}

bool Stage6::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    if(!isError()){
        // Update the status to indicate the stage is active
        setStatus(Stage6PostUse::INIT);
    }

    step();

    return true;
}

void Stage6::stop(){
    controller->setShockCount(0); // Reset
    // Turn off all indicator lights
    controller->setPower(false);
    controller->getPowerIndicator()->setEnabled(false);
    controller->getStageButton(static_cast<int>(Stage::POST_USE))->setEnabled(true);
    controller->getStageLabel(static_cast<int>(Stage::POST_USE))->setEnabled(false);
    setStatus(Stage6PostUse::DONE);

}

bool Stage6::setStatus(Stage6PostUse s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage6::nextStage(){ // @ Override from StageManger
    controller->setStage(Stage::NONE); // Set AED controller's stage to this one

    // Code here
    screen->setStage(Stage::NONE);

    return true;
}

void Stage6::step(){
    // reset shock num and AED setting (time)
    stop();
    nextStage();
}
