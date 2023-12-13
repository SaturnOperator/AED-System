#include "Stage2.h"
#include "AEDController.h" // Forward declare

Stage2::Stage2(AEDController* controller, QObject* parent) :
    StageManager(Stage::PADS, controller, parent) {
   timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage2::step);//Run step() every interval
    timer->start(500); //update every0.5 second
    init = true;
    adultLocal = true;
    showPediatricOption = true;
}

bool Stage2::start(){ // @ Override from StageManger
    intervalCount = 0;

    // Set AED controller's stage to this one
    controller->changeMainstage(stage);
    // Set Screen to this stage
    screen->setStage(stage);

    if(!isError()){
        // Update the status to indicate the stage is active
        setStatus(Stage2Install::INIT);
        return false;
    }

    return true;
}

void Stage2::stop(){
    // Update the status to indicate the stage is done
    setStatus(Stage2Install::DONE);
}

bool Stage2::setStatus(Stage2Install s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}


bool Stage2::nextStage(){ // @ Override from StageManger
    controller->setStage(Stage::ANALYZE); // Set AED controller's stage to this one
    screen->setStage(Stage::ANALYZE); // Set Screen to this stage
    return true;
}

void Stage2::step() {
    // Always check for errors, even when stage isn't active
    if(!checkSafetySystems()){
        return;
    }

    //the screen updates when it is active
    if(!isActive()){
        return;
    }

    const int pause = 6; // 3 seconds

    if(intervalCount == 0){
        showPediatricOption = false; // Don't show this again in the next refresh
        screen->showStage2bToggleChildPatient(!pads->getAdult());
    }

    if(adultLocal != pads->getAdult() && intervalCount < 2*pause){
        screen->showStage2aPads(false);
        adultLocal = pads->getAdult();
        screen->showStage2bToggleChildPatient(!pads->getAdult());
    }

    // Hide button and show chest
    if (intervalCount == 2*pause) {
        screen->hideStage2b();
        screen->showStage2aChest(true);
        screen->showMsg2aExposeChest(true);
    }

    // Show attach pads message
    if(intervalCount == 3*pause){
        screen->showMsg2aAttachPads(true);
    }

    // Blink attach pads indicators
    if (intervalCount >= 3*pause && intervalCount < 4*pause) {
        if (intervalCount % 2 == 0) {
            screen->showStage2aPadsIndicator(true);
        } else {
            screen->showStage2aPadsIndicator(false);
        }
    }

    // Show pads
    if(intervalCount == 4*pause){
        screen->showStage2aPads(true);
    }

    if(pads->isAttached() and init){
        init = false;
    }

    if(pads->isAttached()){
        stop();
        nextStage();
    }

    // Increment intervalCount
    intervalCount++;
}

bool Stage2::checkSafetySystems(){
    // Stage 2 checks if pad is connected to AED and pad is connected to patient
    if(!pads->isConnected()){
        setStatus(Stage2Install::ERROR_CONNECT_PADS);
        start();
        screen->showMsg2aPluginPads(true);
        return false;
    }

    
    if(init){
        // System starts with the pads not connected
        // don't show this error at the start
    } else if (!pads->isAttached()){
        setStatus(Stage2Install::ERROR_ATTACH_PADS);
        start();
        screen->showStage2aChest(true);
        screen->showStage2aPads(true);
        screen->showMsg2aAttachPads(true);
        return false;
    }
    if(!isDone()){
        setStatus(Stage2Install::INIT);
    }
    return true;
}
