#include "AEDController.h"

AEDController::AEDController(QObject* parent)
    : QObject(parent), mainStage(Stage::POWER) {

    screen = new QAEDScreen();
    pads = new Pads();

    powerCapacity = POWER_CAPACITY; // Set battery level to define val
    setShockCount(0); // Start shock count at 0

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
        if(power){
            off();
        } else {
            on();
        }
    });

    connect(pediatricButton, &QPushButton::clicked, [this]() {
        bool adult = pads->getAdult();
        pads->setAdult(!adult);
        pediatricIndicator->setDisabled(pads->getAdult());
    });

    QString labelStyle = QString(
        "QLabel { "
        "    padding: 0px;"
        "    font-family: Frank;"
        "    color: #c9cbbc; "
        "}"
        "QLabel:disabled { "
        "    color: #464e55; "
        "}"
    );

    // Add a button for each stage, do it by looping through all the stages
    for (int i = static_cast<int>(Stage::NONE); i <= static_cast<int>(Stage::POST_USE); i++) {

        Stage currentStage = static_cast<Stage>(i);

        // Create the button
        stageButtons.append(new QIconButton(QString::number(i), true)); // use QIconButton alt design by setting to true
        // Create a label and set it to the current stage's name
        QString stageName = stageToString(currentStage);
        stageLabels.append(new QLabel(stageName));
        stageLabels[i]->setStyleSheet(labelStyle);
        stageLabels[i]->setEnabled(false);

        // continue/ignore if it's the NONE stage
        if(currentStage == Stage::NONE){
            continue; 
        }

        // Make the buttons update the screen when they're pressed
        // The button will change the stage on the screen
        // Also switch the screen settings tab to show settings for that stage
        connect(stageButtons[i], &QPushButton::clicked, [this, currentStage]() {
            if(isOn()){
                getStage(currentStage)->start();
                // settings->setCurrentIndex(i-1);
            }
        });
    }

    batteryLevel = new QProgressBar();
    batteryLevel->setMinimum(0);
    batteryLevel->setMaximum(POWER_CAPACITY);
    batteryLevel->setValue(POWER_CAPACITY);

    // init as powered off
    setStage(Stage::NONE);
    changeMainstage(Stage::NONE);
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
    if(s != Stage::NONE){
        return stages[s]->start();
    }
}

void AEDController::changeMainstage(Stage s){
    mainStage = s;
    for (int i = static_cast<int>(Stage::NONE); i <= static_cast<int>(Stage::POST_USE); i++) {
        Stage currentStage = static_cast<Stage>(i);
        if(s == currentStage){
            stageButtons[i]->setEnabled(false);
            stageLabels[i]->setEnabled(true);
        } else {
            stageButtons[i]->setEnabled(true);
            stageLabels[i]->setEnabled(false);
        }
    }
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
    batteryLevel->setValue(powerCapacity); // Update battery
}

bool AEDController::isSystemFault(){
    return systemFault;
}
bool AEDController::isLowBattery(){
    return powerCapacity < LOW_BAT_THRESHOLD;
}

void AEDController::setShockCount(int num){
    numShocks = num;
    screen->setShockCount(numShocks);
}

void AEDController::addShock(){
    powerCapacity -= SHOCK_POWER_DRAIN; // depleat the battery capacity each shock
    batteryLevel->setValue(powerCapacity); // Update battery
    screen->setShockCount(++numShocks);
}

void AEDController::setPower(bool p){
    power = p;
}

bool AEDController::isOn(){
    return power;
}

void AEDController::on(){
    power = true;
    powerIndicator->setEnabled(true);
    screen->resetTimer();
    getStage(Stage::POWER)->start();
}

void AEDController::off(){
    getStage(Stage::POST_USE)->start();
}

QIconButton* AEDController::getStageButton(int i){
    if(i < 0 || i >= stageButtons.length()){
        return nullptr;
    }
    return stageButtons[i];
}

QLabel* AEDController::getStageLabel(int i){
    if(i < 0 || i >= stageLabels.length()){
        return nullptr;
    }
    return stageLabels[i];
}

QProgressBar* AEDController::getBatteryBar(){
    return batteryLevel;
}
