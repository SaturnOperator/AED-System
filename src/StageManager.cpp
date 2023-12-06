#include "StageManager.h"
#include "AEDController.h" // forward declaration

StageManager::StageManager(Stage s, AEDController* controller, QObject* parent)
    : QObject(parent), stage(s), controller(controller) {
    
    screen = controller->getScreen(); // Pass in the screen from the controller
}