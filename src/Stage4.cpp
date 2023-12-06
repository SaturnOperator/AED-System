#include "Stage4.h"

Stage4::Stage4(AEDController* controller, QObject* parent) : 
    StageManager(Stage::SHOCK, controller, parent) {

    screen->addShock(); // Start shock count 0
    screen->addShock(); // Start shock count 0
}
