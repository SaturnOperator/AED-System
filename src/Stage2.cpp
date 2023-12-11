#include "Stage2.h"
#include "AEDController.h" // Forward declare

Stage2::Stage2(AEDController* controller, QObject* parent) :
    StageManager(Stage::PADS, controller, parent) {
   timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage2::step);//Run step() every interval
    timer->start(500); //update every0.5 second
    init = true;
    adultLocal = true;
    showPediatricOption = false;
    pediatricOptionTime = 0;
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
    if(!checkSafetySystems()){
        return;
    }

    //the screen updates when it is active
    if(!isActive()){
        return;
    }

    const int exposeChestDuration = 6;  // in half-seconds (3 seconds)
    const int attachPadsDuration = 6;   // in half-seconds (3 seconds)
    const int showPadsDuration = 6;     // in half-seconds (3 seconds)
    const int showButtonDuration = 10;     // in half-seconds (5 seconds)

    // Skip instructions if pads attached
    if (pads->isAttached()){
        intervalCount = exposeChestDuration + attachPadsDuration;
    }

    // Check if the expose chest message should be shown
    if (intervalCount == 1) {
        screen->showMsg2aExposeChest(true);
    }

    // Show attach pads message
    if(intervalCount == exposeChestDuration){
        screen->showMsg2aAttachPads(true);
    }

    // Blink attach pads indicators
    if (intervalCount >= exposeChestDuration && intervalCount < exposeChestDuration + attachPadsDuration) {

        
        if ((intervalCount - exposeChestDuration) % 2 == 0) {
            screen->showStage2aPadsIndicator(true);
        } else {
            screen->showStage2aPadsIndicator(false);
        }
    }

    // Check if the pads should be shown
    if (intervalCount == exposeChestDuration + attachPadsDuration) {
        screen->showStage2aPads(true);
    }

    if (pads->isAttached()) {
        init = false;
        pediatricOptionTime = intervalCount;
    }

    // Show pediatric button option
    if(pads->isAttached() && !showPediatricOption && intervalCount > exposeChestDuration + attachPadsDuration + showPadsDuration){
        screen->showStage2bChildPatient();
        showPediatricOption = true; // Don't show this again in the next refresh
        pediatricOptionTime = intervalCount;
    }

    if(pads->isAttached() && adultLocal != pads->getAdult()){
        adultLocal = pads->getAdult();
        screen->showStage2bToggleChildPatient(!pads->getAdult());
    }

    if(pads->isAttached() && intervalCount == (pediatricOptionTime + showButtonDuration)){
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
        screen->showStage2aPads(true);
        screen->showMsg2aAttachPads(true);
        return false;
    }
    setStatus(Stage2Install::INIT);
    return true;
}
