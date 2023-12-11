#include "Stage4.h"
#include "AEDController.h" // Forward declare

Stage4::Stage4(AEDController* controller, QObject* parent) : 
    StageManager(Stage::SHOCK, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage4::step); // Run step() every interval
    timer->start(interval); // Update every 0.5 seconds

    screen->addShock(); // Start shock count 0
}

bool Stage4::start(){ // @ Override from StageManger
    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage

    intervalCount = 0;

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

void Stage4::step(){
    if(controller->getCurrentStage() != stage){
        return;
    }

    const int startDelay = 5;

    if(intervalCount == 1){
        // screen->shockProgress(0);
        screen->showMsg4Shock(true);
    } else if (intervalCount > startDelay && intervalCount < (20 + startDelay)){
        screen->shockProgress(intervalCount-startDelay);
    } else if(intervalCount == (20 + startDelay)){
        stop();
        nextStage();
    }

    intervalCount++;
}