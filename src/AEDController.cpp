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
    screen = new QAEDScreen();
    screenThread = new QThread();
    screen->moveToThread(screenThread); // Put screen on its own thread
    screenThread->start(); // Start the screen thread
}

AEDController::~AEDController()
{
    // Clean up the screen and its thread
    if (screenThread) {
        screenThread->quit();
        screenThread->wait();
        delete screenThread;
    }
    if (screen) {
        delete screen;
    }
}

QAEDScreen* AEDController::getScreen(){
    return screen;
}