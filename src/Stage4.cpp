#include "Stage4.h"
#include "AEDController.h" // Forward declare

Stage4::Stage4(AEDController* controller, QObject* parent) : 
    StageManager(Stage::SHOCK, controller, parent) {

    screen->addShock(); // Start shock count 0
}

bool Stage4::setStatus(Stage4Shock s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage4::activate(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}

bool Stage4::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}