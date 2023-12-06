#include "Stage5.h"

Stage5::Stage5(AEDController* controller, QObject* parent) : 
    StageManager(Stage::CPR, controller, parent) {

    // // Start CPR countdown timer
    screen->startCountdown();
}