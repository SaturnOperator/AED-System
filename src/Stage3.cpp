#include "Stage3.h"
#include "AEDController.h" // Forward declare

Stage3::Stage3(AEDController* controller, QObject* parent) : 
    StageManager(Stage::ANALYZE, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage3::step); // Run step() every interval
    timer->start(100); // Update every 0.1 second  


}

bool Stage3::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    stepCount = 0;

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

void Stage3::step(){
    if(controller->getCurrentStage() != stage){
        return;
    }

    // // Randomly pick one of the many pulse examples
    // int rIndex = 0;
    // if(rhythm == Rhythms::NONE){
    //     return true; // Do nothing else
    // } else if (rhythm == Rhythms::SINUS) {
    //     rIndex = QRandomGenerator::global()->bounded(0,1); // Healthy rhythms 
    // } else if (rhythm == Rhythms::VTACH){
    //     rIndex = QRandomGenerator::global()->bounded(2,4); // VT rhythms
    // } else if (rhythm == Rhythms::VFIB){
    //     rIndex = 5; // Healthy rhythms 
    // } else {
    //     rIndex = QRandomGenerator::global()->bounded(6,7); // Asystole rhythms 
    // }

    if(stepCount == 5){
        screen->showMsg3aStandBack(true);
    } else if (stepCount == 20){
        screen->showMsg3aAnalyzing(true);
    } else if (stepCount == 40){
        screen->stage3bECG();
        ecgPercent = 100;
        rIndex;
        screen->sweepEcg(rIndex, ecgPercent);
        screen->showRhythm(rIndex);
    }

    if(stepCount > 40){
        screen->sweepEcg(rIndex, ecgPercent);
        ecgPercent -= 3;
    }

    if(stepCount == 60){
        screen->showLabel3bSinus(true);
        screen->setBpm(100);
    }

    stepCount++;
}