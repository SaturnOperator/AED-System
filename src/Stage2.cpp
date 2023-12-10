#include "Stage2.h"
#include "AEDController.h" // Forward declare

Stage2::Stage2(AEDController* controller, QObject* parent) :
    StageManager(Stage::PADS, controller, parent) {
   timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stage2::step);//Run step() every interval
    timer->start(500); //update every0.5 second
}

bool Stage2::start(){ // @ Override from StageManger
  
    //added

    // Set AED controller's stage to this one
    controller->changeMainstage(stage);

    // Set Screen to this stage
    screen->setStage(stage);

    // Show the pads installation messages on the screen
    screen->showStage2aPadsIndicator(false);
    screen->showStage2aPads(false);
    screen->showMsg2aExposeChest(false);
    screen->showMsg2aAttachPads(false);


    // Update the status to indicate the stage is active
    setStatus(Stage2Install::INIT); // Use a meaningful status code


    return true;
}

void Stage2::stop(){
    // Code here
    //added
    screen->clearMsg2a();

      // Update the status to indicate the stage is done
    timer->stop(); // Stop timer
    setStatus(Stage2Install::IDLE); // Use a meaningful status code
    //added
}

bool Stage2::setStatus(Stage2Install s){ // @ Overload from StageManger
    status = static_cast<int>(s);
    return true;
}


bool Stage2::nextStage(){ // @ Override from StageManger
    controller->setStage(stage); // Set AED controller's stage to this one

    //added
    // Update the status to indicate the stage is done
    setStatus(Stage2Install::DONE); // Use a meaningful status code
    //added

    return true;
}

void Stage2::step() {
    //the screen updates when it is active
    if(!isActive()){
        return;
    }

    const int exposeChestDuration = 6;  // in half-seconds (3 seconds)
    const int attachPadsDuration = 6;   // in half-seconds (3 seconds)
    const int showPadsDuration = 6;     // in half-seconds (3 seconds)

    // Check if the expose chest message should be shown
    if (intervalCount < exposeChestDuration) {
        screen->showMsg2aExposeChest(true);
    } else {
        screen->showMsg2aExposeChest(false);
    }

    // Check if the attach pads message and indicator should be shown
    if (intervalCount >= exposeChestDuration && intervalCount < exposeChestDuration + attachPadsDuration) {
        screen->showMsg2aAttachPads(true);

        // Blink the indicator every second
        if ((intervalCount - exposeChestDuration) % 2 == 0) {
            screen->showStage2aPadsIndicator(true);
        } else {
            screen->showStage2aPadsIndicator(false);
        }
    } else {
        screen->showMsg2aAttachPads(false);
        screen->showStage2aPadsIndicator(false);
    }

    // Check if the pads should be shown
    if (intervalCount >= exposeChestDuration + attachPadsDuration &&
        intervalCount < exposeChestDuration + attachPadsDuration + showPadsDuration) {
        screen->showStage2aPads(true);
    } else {
        screen->showStage2aPads(false);
    }

    if (intervalCount == exposeChestDuration + attachPadsDuration + showPadsDuration) {
        if (pads->isAttached()) {
            // Show the child patient option or perform other actions
            screen->showStage2bChildPatient();
            screen->showStage2bToggleChildPatient(true);

            setStatus(Stage2Install::DONE);
        } else {
            // Pads are not attached, update status accordingly
            setStatus(Stage2Install::ERROR_CONNECT_PADS);
        }
    }


    // Increment intervalCount
    intervalCount++;


}
