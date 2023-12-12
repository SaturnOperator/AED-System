#include "Stage4.h"
#include "AEDController.h" // Forward declare

Stage4::Stage4(AEDController* controller, QObject* parent) : 
    StageManager(Stage::SHOCK, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage4::step); // Run step() every interval
    timer->start(interval); // Update every 0.5 seconds
}

bool Stage4::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    intervalCount = 0;
    shocked = false;

    return true;
}

void Stage4::stop(){
    setStatus(Stage4Shock::DONE);
}

bool Stage4::setStatus(Stage4Shock s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage4::nextStage(){ // @ Override from StageManger
    controller->setStage(Stage::CPR);
    screen->setStage(Stage::CPR);
    return true;
}

bool Stage4::checkShockableRhythm(){
    return pads->getRhythm() == Rhythms::VFIB || pads->getRhythm() == Rhythms::VTACH;
}

void Stage4::step(){
    if(controller->getCurrentStage() != stage){
        return;
    }

    // Check for errors during stage
    if(!checkSafetySystems()){
        return;
    }
 
    const int startDelay = 5;

    if(checkShockableRhythm()){
        if(intervalCount == 1){
            screen->showMsg4Shock(true);
        } else if (intervalCount > startDelay && intervalCount < (20 + startDelay)){
            if(!screen->shockProgress(intervalCount-startDelay) && !shocked){
                controller->addShock(); // End reached, delivery shock
                shocked = true; // Don't shock again after this
            }
        } else if (intervalCount == 10 + startDelay){
        } else if(intervalCount == (20 + startDelay)){
            stop();
            nextStage();
        }
    } else {
        screen->showMsg4NoShock(true);
        if(intervalCount == 2*startDelay){
            stop();
            nextStage();
        }
    }



    intervalCount++;
}

bool Stage4::checkSafetySystems(){
    // Make sure patient isn't being touched while ECG is analyzed
    if(pads->getDepth() != 0){
        setStatus(Stage4Shock::ERROR_DONT_TOUCH);
        start();
        screen->showMsg4DontTouch(true);
        return false;
    }
    if(!isDone()){
        setStatus(Stage4Shock::INIT);
    }
    return true;
}