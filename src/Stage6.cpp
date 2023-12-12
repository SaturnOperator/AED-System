#include "Stage6.h"
#include "AEDController.h" // Forward declare

Stage6::Stage6(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POST_USE, controller, parent) {

}

bool Stage6::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    // Code here
    if(!isError()){
        // Update the status to indicate the stage is active
        setStatus(Stage6PostUse::INIT);
        return false;
    }
    return true;
}

void Stage6::stop(){
    // Code here    
    setStatus(Stage6PostUse::DONE);
    qInfo() <<"stage6: done";

}

bool Stage6::setStatus(Stage6PostUse s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage6::nextStage(){ // @ Override from StageManger
    controller->setStage(Stage::POWER); // Set AED controller's stage to this one

    // Code here
    screen->setStage(Stage::POWER);

    return true;
}

void Stage6::step(){
    if(!isActive()){
        return;
    }

    // reset shock num and AED setting(time)
    controller->setShockCount(0);
}
