#include "QScreenSettings.h"

#include <QRandomGenerator> //@@ remove

QScreenSettings::QScreenSettings(AEDController* controller, QWidget *parent)
    : QTabWidget(parent), controller(controller) {

    /* Stage 5 settings */
    stage1Init();
    stage2Init();
    stage3Init();
    stage4Init();
    stage5Init();
    stage6Init();
}

QScreenSettings::~QScreenSettings(){}

void QScreenSettings::stage1Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);

    //@@@

    this->addTab(stageTab, stageToString(Stage::POWER));
}

void QScreenSettings::stage2Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);

    // Show pads indicator
    QCheckBox* checkbox1 = new QCheckBox();
    layout->addRow("Pads Indicator", checkbox1);
    // Update on value change
    connect(checkbox1, &QCheckBox::stateChanged, [this](int state) {
        controller->getScreen()->showStage2aPadsIndicator(state == Qt::Checked);
    });

    // Show pads installation
    QCheckBox* checkbox2 = new QCheckBox();
    layout->addRow("Pads", checkbox2);
    // Update on value change
    connect(checkbox2, &QCheckBox::stateChanged, [this](int state) {
        controller->getScreen()->showStage2aPads(state == Qt::Checked);
    });

    /* Stage 2 Messages */

    // Show message: Expose Chest
    QPushButton* msgButton1 = new QPushButton("Expose Chest");
    layout->addRow("Message:", msgButton1);
    connect(msgButton1, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg2aExposeChest(true);
    });

    // Show message: Attach Pads
    QPushButton* msgButton2 = new QPushButton("Attach Pads");
    layout->addRow("Message:", msgButton2);
    connect(msgButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg2aAttachPads(true);
    });

    // Clear all messages
    QPushButton* clearMsgButton = new QPushButton("Clear");
    layout->addRow("Clear all messages:", clearMsgButton);
    connect(clearMsgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearMsg2a();
    });

    // Show child patient option
    QPushButton* childPatientButton = new QPushButton("Show option");
    layout->addRow("Child Patient:", childPatientButton);
    connect(childPatientButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->showStage2bChildPatient();
    });

    // Child patient toggle
    QCheckBox* checkbox3 = new QCheckBox();
    layout->addRow("Child Patient", checkbox3);
    // Update on value change
    connect(checkbox3, &QCheckBox::stateChanged, [this](int state) {
        controller->getScreen()->showStage2bToggleChildPatient(state == Qt::Checked);
    });




    this->addTab(stageTab, stageToString(Stage::PADS));
}

void QScreenSettings::stage3Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);
    
    /* Stage 3 Messages */

    // Show message: Analyzing
    QPushButton* msgButton1 = new QPushButton("Analyzing");
    layout->addRow("Message:", msgButton1);
    connect(msgButton1, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg3aAnalyzing(true);
    });

    // Show message: Do not touch
    QPushButton* msgButton2 = new QPushButton("Do not touch");
    layout->addRow("Message:", msgButton2);
    connect(msgButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg3aDontTouch(true);
    });

    // Show message: Stand back
    QPushButton* msgButton3 = new QPushButton("Stand Back");
    layout->addRow("Message:", msgButton3);
    connect(msgButton3, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg3aStandBack(true);
    });

    // Clear all messages
    QPushButton* clearMsgButton = new QPushButton("Clear");
    layout->addRow("Clear all messages:", clearMsgButton);
    connect(clearMsgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearMsg3a();
    });

    QPushButton* ecgButton = new QPushButton("ECG");
    layout->addRow("Show ECG:", ecgButton);
    connect(ecgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->stage3bECG();
    });

    QPushButton* ecgLabel1 = new QPushButton("Sinus");
    layout->addRow("Categorize ECG:", ecgLabel1);
    connect(ecgLabel1, &QPushButton::clicked, [this]() {
        controller->getScreen()->showLabel3bSinus(true);
    });

    QPushButton* ecgLabel2 = new QPushButton("VF");
    layout->addRow("Categorize ECG:", ecgLabel2);
    connect(ecgLabel2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showLabel3bVF(true);
    });

    QPushButton* ecgLabel3 = new QPushButton("VT");
    layout->addRow("Categorize ECG:", ecgLabel3);
    connect(ecgLabel3, &QPushButton::clicked, [this]() {
        controller->getScreen()->showLabel3bVT(true);
    });

    QPushButton* ecgLabel4 = new QPushButton("Asystole");
    layout->addRow("Categorize ECG:", ecgLabel4);
    connect(ecgLabel4, &QPushButton::clicked, [this]() {
        controller->getScreen()->showLabel3bAsystole(true);
    });


    QPushButton* ecgLabelClear = new QPushButton("Clear");
    layout->addRow("Clear ECG Label:", ecgLabelClear);
    connect(ecgLabelClear, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearLabel3b();
    });

    QPushButton* ecg0Button = new QPushButton("0");
    layout->addRow("Show ECG:", ecg0Button);
    connect(ecg0Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(0);
    });

    QPushButton* ecg1Button = new QPushButton("1");
    layout->addRow("Show ECG:", ecg1Button);
    connect(ecg1Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(1);
    });

    QPushButton* ecg2Button = new QPushButton("2");
    layout->addRow("Show ECG:", ecg2Button);
    connect(ecg2Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(2);
    });

    QPushButton* ecg3Button = new QPushButton("3");
    layout->addRow("Show ECG:", ecg3Button);
    connect(ecg3Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(3);
    });

    QPushButton* ecg4Button = new QPushButton("4");
    layout->addRow("Show ECG:", ecg4Button);
    connect(ecg4Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(4);
    });

    QPushButton* ecg5Button = new QPushButton("5");
    layout->addRow("Show ECG:", ecg5Button);
    connect(ecg5Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(5);
    });

    QPushButton* ecg6Button = new QPushButton("6");
    layout->addRow("Show ECG:", ecg6Button);
    connect(ecg6Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(6);
    });

    QPushButton* ecg7Button = new QPushButton("7");
    layout->addRow("Show ECG:", ecg7Button);
    connect(ecg7Button, &QPushButton::clicked, [this]() {
        controller->getScreen()->showRhythm(7);
    });

    QPushButton* bpmButton = new QPushButton("random");
    layout->addRow("Set BPM:", bpmButton);
    connect(bpmButton, &QPushButton::clicked, [this]() {
        int randomInt = QRandomGenerator::global()->bounded(100);
        controller->getScreen()->setBpm(randomInt);
    });

    /* Slider for compression level */ 
    QSlider* ecgSlider = new QSlider(Qt::Horizontal);
    ecgSlider->setMinimum(0);
    ecgSlider->setMaximum(100);
    layout->addRow("ECG", ecgSlider);
    // Update on value change
    connect(ecgSlider, &QSlider::valueChanged, [this, ecgSlider]() {
        controller->getScreen()->sweepEcg(ecgSlider->value());
    });

    


    this->addTab(stageTab, stageToString(Stage::ANALYZE));
}

void QScreenSettings::stage4Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);

    //@@@

    this->addTab(stageTab, stageToString(Stage::SHOCK));
}

/* Stage 5: CPR screen toggles */
void QScreenSettings::stage5Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);

    /* Slider for compression level */ 
    QSlider* compressionLevel = new QSlider(Qt::Horizontal);
    compressionLevel->setMinimum(0);
    compressionLevel->setMaximum(11);
    layout->addRow("Compression Depth", compressionLevel);
    // Update on value change
    connect(compressionLevel, &QSlider::valueChanged, [this, compressionLevel]() {
        // controller->getStage(Stage::CPR)->setDepth(compressionLevel);
        static_cast<Stage5*>(controller->getStage(Stage::CPR))->setDepth(compressionLevel->value());
    });


    /* Stage 5 Messages */

    // Show message: Good Compression
    QPushButton* msgButton1 = new QPushButton("Good Compression");
    layout->addRow("Message:", msgButton1);
    connect(msgButton1, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg5GoodCompression(true);
    });

    // Show message: Push Harder
    QPushButton* msgButton2 = new QPushButton("Push Harder");
    layout->addRow("Message:", msgButton2);
    connect(msgButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg5PushHarder(true);
    });

    // Show message: Start CPR
    QPushButton* msgButton3 = new QPushButton("Start CPR");
    layout->addRow("Message:", msgButton3);
    connect(msgButton3, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg5StartCpr(true);
    });

    // Show message: Stop CPR
    QPushButton* msgButton4 = new QPushButton("Stop CPR");
    layout->addRow("Message:", msgButton4);
    connect(msgButton4, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg5StopCpr(true);
    });

    // Clear all messages
    QPushButton* clearMsgButton = new QPushButton("Clear");
    layout->addRow("Clear all messages:", clearMsgButton);
    connect(clearMsgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearMsg5();
    });

    // Increase shock count
    QPushButton* testButton2 = new QPushButton("add shock");
    layout->addRow("Shock count:", testButton2);
    connect(testButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->addShock();
    });

    this->addTab(stageTab, stageToString(Stage::CPR));
}

void QScreenSettings::stage6Init(){
    QWidget* stageTab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stageTab->setLayout(layout);

    //@@@

    this->addTab(stageTab, stageToString(Stage::POST_USE));
}