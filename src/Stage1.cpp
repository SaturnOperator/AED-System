#include "Stage1.h"
#include "AEDController.h" // Forward declare

Stage1::Stage1(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POWER, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage1::step); // Run step() every interval
    timer->start(interval); // Update every 3 seconds
}

bool Stage1::start(){ // @ Override from StageManger
    instruction = 0; // Used to itterate through the list instructions
    intervalCount = 0;
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    if(!isError()){
        setStatus(Stage1Power::INIT);
        return false;
    }

    return true;
}

void Stage1::stop(){
    setInstruction(0); // Reset instructions so none are highlighted
    setStatus(Stage1Power::DONE);
}

bool Stage1::setStatus(Stage1Power s){ // @ Overload from StageManger
    // status = static_cast<int>(s);
    status = s;
    return true;
}

bool Stage1::nextStage(){ // @ Override from StageManger
    controller->setStage(Stage::PADS); // Set AED controller's stage to this one
    screen->setStage(Stage::PADS); // Set Screen to this stage
    return true;
}

void Stage1::step(){
    qInfo() << intervalCount;
    // Check for errors, if any change the screen and display them
    if(!checkSafetySystems()){
        return;
    }

    // Do not proceed if it is not the current stage
    if(controller->getCurrentStage() != stage){
        return;
    }

    // Start by showing Unit Ok
    if(intervalCount == 1){
        screen->showMsg1UnitOk(true);
    }

    // Show new instructions every 4 seconds
    if(intervalCount == 2 || intervalCount % 6 == 0){
        screen->showInstruction1(instruction);
        instruction++;
    }

    // Change instruction every 3 seconds
    if(instruction >= 6){
        stop();
        nextStage();
        return;
    }

    intervalCount++;
}

bool Stage1::checkSafetySystems(){
    // Stage 1 checks if battery has enough charge and for no system faults
    if(controller->isSystemFault()){
        setStatus(Stage1Power::ERROR_SYSTEM_FAULT);
        start();
        screen->showMsg1SysFault(true);
        return false;
    }
    if(controller->isLowBattery()){
        setStatus(Stage1Power::ERROR_LOW_BATTERY);
        start();
        screen->showMsg1LowBat(true);
        return false;
    }
    return true;
}

bool Stage1::setInstruction(int i){
    instruction = i;
    screen->showInstruction1(i);
    return true;
}