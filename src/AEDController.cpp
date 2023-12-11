#include "AEDController.h"

AEDController::AEDController(QObject* parent)
    : QObject(parent), mainStage(Stage::POWER) {

    powerCapacity = POWER_CAPACITY; // Set battery level to define

    screen = new QAEDScreen();
    pads = new Pads();

    // screenThread = new QThread();
    // screen->moveToThread(screenThread); // Put screen on its own thread
    // screenThread->start(); // Start the screen thread

    // Create manager for each stage
    stages[Stage::POWER] = new Stage1(this);
    stages[Stage::PADS] = new Stage2(this);
    stages[Stage::ANALYZE] = new Stage3(this);
    stages[Stage::SHOCK] = new Stage4(this);
    stages[Stage::CPR] = new Stage5(this);
    stages[Stage::POST_USE] = new Stage6(this);

    // Put Stage Manager instance on its own thread 
    for (auto stage : stages.keys()) {
        // Create and store threads for each stage
        stageThreads[stage] = new QThread();
        // Move Stage instances to their respective threads
        stages[stage]->moveToThread(stageThreads[stage]);
        // Start the threads
        stageThreads[stage]->start();
    }

    // Create buttons for power and pediatric option
    powerButton = new QIconButton("");
    pediatricButton = new QIconButton("");
    powerButton->setSize(100);
    pediatricButton->setSize(100);

    // Create status indicator for pediatric option
    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();
    powerIndicator = new QLabel("");
    pediatricIndicator = new QLabel("");

    // Init disabled
    powerIndicator->setEnabled(false);
    pediatricIndicator->setDisabled(pads->getAdult());

    QString indicatorStyle = QString(
        "QLabel { "
        "    font-size: 10px;"
        "    color: #de4c33; "
        "}"
        "QLabel:disabled { "
        "    color: #442c3b; "
        "}"
    );

    powerIndicator->setStyleSheet(indicatorStyle);
    pediatricIndicator->setStyleSheet(indicatorStyle);
    powerIndicator->setFont(iconsFont);
    pediatricIndicator->setFont(iconsFont);
    powerIndicator->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    pediatricIndicator->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

    // Connect buttons
    connect(powerButton, &QPushButton::clicked, [this]() {
        // controller->getScreen()->showMsg1UnitOk(true);
        qInfo() << "@@@ Power button not enabled yet";
    });

    connect(pediatricButton, &QPushButton::clicked, [this]() {
        bool adult = pads->getAdult();
        pads->setAdult(!adult);
        pediatricIndicator->setDisabled(pads->getAdult());
    });

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
    return stages[s]->start();
}

void AEDController::changeMainstage(Stage s){
    mainStage = s;
}

QAEDScreen* AEDController::getScreen(){
    return screen;
}

Pads* AEDController::getPads(){
    return pads;
}

StageManager* AEDController::getStage(Stage s){
    return stages[s];
}

Stage AEDController::getCurrentStage(){
    return mainStage;
}

QIconButton* AEDController::getPowerButton(){
    return powerButton;
}

QIconButton* AEDController::getPediatricButton(){
    return pediatricButton;
}

QLabel* AEDController::getPowerIndicator(){
    return powerIndicator;
}

QLabel* AEDController::getPediatricIndicator(){
    return pediatricIndicator;
}

void AEDController::setSystemFault(bool fault){
    systemFault = fault;
}

void AEDController::setPowerCapacity(int capacity){
    powerCapacity = capacity;
}

bool AEDController::isSystemFault(){
    return systemFault;
}
bool AEDController::isLowBattery(){
    return powerCapacity < LOW_BAT_THRESHOLD;
}