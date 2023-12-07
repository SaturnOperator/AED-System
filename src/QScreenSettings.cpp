#include "QScreenSettings.h"

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
        controller->getScreen()->showStage2PadsIndicator(state == Qt::Checked);
    });

    // Show pads installation
    QCheckBox* checkbox2 = new QCheckBox();
    layout->addRow("Pads", checkbox2);
    // Update on value change
    connect(checkbox2, &QCheckBox::stateChanged, [this](int state) {
        controller->getScreen()->showStage2Pads(state == Qt::Checked);
    });

    /* Stage 2 Messages */

    // Show message: Expose Chest
    QPushButton* msgButton1 = new QPushButton("Expose Chest");
    layout->addRow("Message:", msgButton1);
    connect(msgButton1, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg2ExposeChest(true);
    });

    // Show message: Attach Pads
    QPushButton* msgButton2 = new QPushButton("Attach Pads");
    layout->addRow("Message:", msgButton2);
    connect(msgButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg2AttachPads(true);
    });

    // Clear all messages
    QPushButton* clearMsgButton = new QPushButton("Clear");
    layout->addRow("Clear all messages:", clearMsgButton);
    connect(clearMsgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearMsg2();
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
        controller->getScreen()->showMsg3Analyzing(true);
    });

    // Show message: Do not touch
    QPushButton* msgButton2 = new QPushButton("Do not touch");
    layout->addRow("Message:", msgButton2);
    connect(msgButton2, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg3DontTouch(true);
    });

    // Show message: Stand back
    QPushButton* msgButton3 = new QPushButton("Stand Back");
    layout->addRow("Message:", msgButton3);
    connect(msgButton3, &QPushButton::clicked, [this]() {
        controller->getScreen()->showMsg3StandBack(true);
    });

    // Clear all messages
    QPushButton* clearMsgButton = new QPushButton("Clear");
    layout->addRow("Clear all messages:", clearMsgButton);
    connect(clearMsgButton, &QPushButton::clicked, [this]() {
        controller->getScreen()->clearMsg3();
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