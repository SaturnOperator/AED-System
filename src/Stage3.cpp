#include "Stage3.h"
#include "AEDController.h" // Forward declare

Stage3::Stage3(AEDController* controller, QObject* parent) : 
    StageManager(Stage::ANALYZE, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage3::step); // Run step() every interval
    timer->start(100); // Update every 0.1 second  

    screen->setBpm(0);
}

bool Stage3::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    stepCount = 0;

    return true;
}

void Stage3::stop(){
    setStatus(Stage3Analyze::DONE);
}

bool Stage3::setStatus(Stage3Analyze s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage3::nextStage(){ // @ Override from StageManger
    Rhythms r = pads->getRhythm();
    // If rhythm is restored to normal sinus rhythm, stop AED system
    // Otherwise continue to shock
    if(r == Rhythms::SINUS){
        controller->setStage(Stage::POST_USE);
        screen->setStage(Stage::POST_USE);
    } else {
        controller->setStage(Stage::SHOCK); 
        screen->setStage(Stage::SHOCK); 
    }
    return true;
}

void Stage3::step(){
    if(controller->getCurrentStage() != stage){
        return;
    }

    // Check for errors during stage
    if(!checkSafetySystems()){
        return;
    }

    if(stepCount == 5){
        screen->showMsg3aStandBack(true);
    } else if (stepCount == 20){
        screen->showMsg3aAnalyzing(true);
    } else if (stepCount == 40){
        screen->stage3bECG();
        ecgPercent = 100;
        rIndex = getECGRhythmIndex(pads->getRhythm());
        screen->sweepEcg(rIndex, ecgPercent);
        screen->showRhythm(rIndex);
    }

    // Optimize in future use
    if(stepCount > 40 && stepCount < 100){
        screen->sweepEcg(rIndex, ecgPercent);
        ecgPercent -= 3;
    }

    if(stepCount == 60){
        Rhythms r = pads->getRhythm();
        if(r == Rhythms::SINUS){
            screen->showLabel3bSinus(true);
        } else if (r == Rhythms::VFIB){
            screen->showLabel3bVF(true);
        } else if (r == Rhythms::VTACH){
            screen->showLabel3bVT(true);
        } else if (r == Rhythms::ASYSTOLE){
            screen->showLabel3bAsystole(true);
        } 

        screen->setBpm(pads->getBpm());
    }

    // End case
    if(stepCount == 100){
        stop();
        nextStage();
    }

    stepCount++;
}

int Stage3::getECGRhythmIndex(Rhythms rhythm){
    // Randomly pick one of the many pulse examples
    if(rhythm == Rhythms::NONE){
        return -1; // Do nothing else
    } else if (rhythm == Rhythms::SINUS) {
        return QRandomGenerator::global()->bounded(0,1); // Healthy rhythms indexes 
    } else if (rhythm == Rhythms::VTACH){
        return QRandomGenerator::global()->bounded(2,4); // VT rhythms indexes
    } else if (rhythm == Rhythms::VFIB){
        return 5; // Only one VFIB rhythm
    } else {
        return QRandomGenerator::global()->bounded(6,7); // Asystole rhythms indexes
    }
}

bool Stage3::checkSafetySystems(){
    // Make sure patient isn't being touched while ECG is analyzed
    if(pads->getDepth() != 0){
        setStatus(Stage3Analyze::ERROR_DONT_TOUCH);
        start();
        screen->showMsg3aDontTouch(true);
        return false;
    }
    if(!isDone()){
        setStatus(Stage3Analyze::INIT);
    }
    return true;
}