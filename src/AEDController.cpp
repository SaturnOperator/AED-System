#include "AEDController.h"

AEDController::AEDController(QObject* parent)
    : QObject(parent), mainStage(Stage::POWER)
{
    screen = new QAEDScreen();
    screenThread = new QThread();
    screen->moveToThread(screenThread); // Put screen on its own thread
    screenThread->start(); // Start the screen thread

    // Create manager for each stage
    stages[Stage::POWER] = new Stage1(this);
    stages[Stage::PADS] = new Stage2(this);
    stages[Stage::ANALYZE] = new Stage3(this);
    stages[Stage::SHOCK] = new Stage4(this);
    stages[Stage::CPR] = new Stage5(this);
    stages[Stage::POST_USE] = new Stage6(this);

    for (auto stage : stages.keys()) {
        // Create and store threads for each stage
        stageThreads[stage] = new QThread();
        // Move Stage instances to their respective threads
        stages[stage]->moveToThread(stageThreads[stage]);
        // Start the threads
        stageThreads[stage]->start();
    }
}


AEDController::~AEDController(){
    for (auto stage : stages.keys()) {
        delete stageThreads[stage];
        delete stages[stage];
    }

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

bool AEDController::setStage(Stage s){
    return stages[s]->activate();
}


QAEDScreen* AEDController::getScreen(){
    return screen;
}