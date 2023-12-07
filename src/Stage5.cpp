#include "Stage5.h"
#include "AEDController.h" // Forward declare

Stage5::Stage5(AEDController* controller, QObject* parent) : 
    StageManager(Stage::CPR, controller, parent) {

    cprIndicator = true; // Used by metronome to set BPM

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage5::metronomeClick);
    timer->start(500); // Update every 0.5 second (120 BPM)    
}

bool Stage5::setStatus(Stage5CPR s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage5::activate(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->startCountdown();
    setStatus(Stage5CPR::INIT);
    return true;
}

bool Stage5::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one
    screen->startCountdown();
    return true;
}

void Stage5::metronomeClick(){
    if(isActive()){
        cprIndicator = !cprIndicator; // Invert state
        screen->showStage5CPRIndicator(cprIndicator);
    }
}