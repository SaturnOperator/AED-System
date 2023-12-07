#include "Stage5.h"
#include "AEDController.h" // Forward declare

Stage5::Stage5(AEDController* controller, QObject* parent) : 
    StageManager(Stage::CPR, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage5::step); // Run step() every interval
    timer->start(interval); // Update every 0.5 second (120 BPM)  

    maxTicks = CPR_COUNTDOWN_DURATION * (1000/interval); // Calculate how many ticks under CPR ends
}

bool Stage5::start(){ // @ Override from StageManger
    cprIndicator = true; // Used by metronome to set BPM
    intervalCount = 0;
    depth = 0;
    lastDepth = 0;

    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage
    setStatus(Stage5CPR::INIT);

    qInfo() << "start cpr: " << screen->showMsg5StartCpr(true);
    screen->startCountdown();

    qInfo() << "Starting CPR Stage";

    return true;
}

void Stage5::stop(){
    timer->stop(); // Stop timer
    setDepth(0); // Reset depth bar
    setStatus(Stage5CPR::DONE);
}

bool Stage5::setStatus(Stage5CPR s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}

bool Stage5::nextStage(){ // @ Override from StageManger
    // controller->getStage(Stage::); // Set AED controller's stage to this one
    return true;
}

void Stage5::step(){
    if(!isActive()){
        return;
    }

    // Stop CPR after set time, show stop CPR 
    if(intervalCount == maxTicks){
        screen->showMsg5StopCpr(true);
        return;
    } else if (intervalCount == maxTicks + 10){
        stop();
        return;
    }

    cprIndicator = !cprIndicator; // Invert state
    screen->showStage5CPRIndicator(cprIndicator);
    
    if(intervalCount % 4 == 0){ // Check compression level every second tick
        checkCompression();
    }

    // Keep track of how long compressions haven't been done
    if(depth == lastDepth){
        idleCount++;
    } else {
        idleCount = 0;
    }
    lastDepth = depth;
    intervalCount++;
}

bool Stage5::setDepth(int d){
    depth = d;
    screen->setStage5CompressionLevel(depth);
    return true;
}

void Stage5::checkCompression(){
    if(!isActive()){
        return;
    }

    if(controller->getStage(Stage::PADS)->isDone()){
        qInfo() << "Stage5 ERROR: Pads not installed - @@ change this later";
    }

    if(idleCount >= 12){
        screen->showMsg5StartCpr(true);
        return;
    }

    if(depth > 0 && depth < 8){
        screen->showMsg5PushHarder(true);
    } else if (depth >= 8){
        screen->showMsg5GoodCompression(true);
    }
    return;
}