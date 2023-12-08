#include "Stage1.h"
#include "AEDController.h" // Forward declare

Stage1::Stage1(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POWER, controller, parent) {

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage1::step); // Run step() every interval
    timer->start(interval); // Update every 3 seconds
    
    maxTicks = 5;

}

bool Stage1::start(){ // @ Override from StageManger
    instructionNum = 0; // Used to itterate through the list instructions
    instruction = 0;

    controller->changeMainstage(stage); // Set AED controller's stage to this one
    screen->setStage(stage); // Set Screen to this stage
    
    // // Check conditions before allowing the AED to power on
    // if (check if there is sufficient battery) {
    //     qInfo() << "Insufficient power. AED cannot power on.";
    //     return false;
    // }

    // if (check if the self test passed) {
    //     qInfo() << "Self-test failed. AED cannot power on.";
    //     return false;
    // }

    // if (check if the pads are connected) {
    //     qInfo() << "Pads are not working. AED cannot power on.";
    //     return false;
    // }

    
    qInfo() << "Power On";

    setStatus(Stage1Power::INIT);

    qInfo() << "UNIT OKAY" << screen->showMsg1UnitOk(true);

    return true;
}

void Stage1::stop(){
    timer->stop(); // Stop timer
    setInstruction(0); // Reset instructions so none are highlighted
    setStatus(Stage1Power::DONE);
}

bool Stage1::setStatus(Stage1Power s){ // @ Overload from StageManger
    // status = static_cast<int>(s);
    status = s;
    return true;
}

bool Stage1::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    // Code here

    return true;
}

void Stage1::step(){

    // if(controller->getCurrentStage() != Stage::POWER){
    //     return;
    // }

    if(instructionNum <= maxTicks){
        qInfo() << "Messages..." << screen->showInstruction1(instructionNum);
    } else {
        stop();
        return;
    }

    instructionNum++;
    
}

bool Stage1::setInstruction(int i){
    instruction = i;
    screen->showInstruction1(0);
    return true;
}