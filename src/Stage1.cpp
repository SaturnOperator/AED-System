#include "Stage1.h"

Stage1::Stage1(AEDController* controller, QObject* parent) : 
    StageManager(Stage::POWER, controller, parent) {

}