#include "AEDController.h"

AEDController::AEDController(QObject* parent)
    : QObject(parent), mainStage(Stage::POWER),
      substage1(Stage1Power::INIT),
      substage2(Stage2Install::INIT),
      substage3(Stage3Analyze::INIT),
      substage4(Stage4Shock::INIT),
      substage5(Stage5CPR::INIT),
      substage6(Stage6PostUse::INIT)
{
    screen->moveToThread(screenThread);
    screenThread->start();
}

AEDController::~AEDController() {
    // Cleanup and stop the screen thread
    screenThread->quit();
    screenThread->wait();
}
