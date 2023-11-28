#include "QScreenSettings.h"

QScreenSettings::QScreenSettings(QAEDScreen* aedScreen, QWidget *parent)
    : QTabWidget(parent), screen(aedScreen) {

    /* Stage 5 settings */
    stage5Init();
}

QScreenSettings::~QScreenSettings(){}


void QScreenSettings::stage5Init(){
    QWidget* stage5Tab = new QWidget();
    QFormLayout* layout = new QFormLayout();
    stage5Tab->setLayout(layout);

    /* Slider for compression level */ 
    QSlider* compressionLevel = new QSlider(Qt::Horizontal);
    compressionLevel->setMinimum(0);
    compressionLevel->setMaximum(11);
    layout->addRow("Compression Depth", compressionLevel);
    // Update on value change
    connect(compressionLevel, &QSlider::valueChanged, [this, compressionLevel]() {
        screen->setCompressionLevel(compressionLevel->value());
    });

    /* Message boxes */

    // Msg: Good compression
    QCheckBox* msg5CheckboxGoodCompression = new QCheckBox();
    layout->addRow("Msg: Good Compression", msg5CheckboxGoodCompression);
    // Update on value change
    connect(msg5CheckboxGoodCompression, &QCheckBox::stateChanged, [this](int state) {
        screen->showMsg5GoodCompression(state == Qt::Checked);
    });

    // Msg: Push harder
    QCheckBox* msg5CheckboxPushHarder = new QCheckBox();
    layout->addRow("Msg: Push Harder", msg5CheckboxPushHarder);
    // Update on value change
    connect(msg5CheckboxPushHarder, &QCheckBox::stateChanged, [this](int state) {
        screen->showMsg5PushHarder(state == Qt::Checked);
    });

    // Msg: Start CPR
    QCheckBox* msg5CheckboxStartCpr = new QCheckBox();
    layout->addRow("Msg: Start CPR", msg5CheckboxStartCpr);
    // Update on value change
    connect(msg5CheckboxStartCpr, &QCheckBox::stateChanged, [this](int state) {
        screen->showMsg5StartCpr(state == Qt::Checked);
    });

    // Msg: Stop CPR
    QCheckBox* msg5CheckboxStopCpr = new QCheckBox();
    layout->addRow("Msg: STOP CPR", msg5CheckboxStopCpr);
    // Update on value change
    connect(msg5CheckboxStopCpr, &QCheckBox::stateChanged, [this](int state) {
        screen->showMsg5StopCpr(state == Qt::Checked);
    });


    this->addTab(stage5Tab, stageToString(Stage::CPR));
}