#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H

#include "defs.h"
#include "QCustomIconsFont.h"

#include "QAEDScreen.h"
#include "StageManager.h"
#include "aed_stages.h"
#include "QIconButton.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"
#include "Pads.h"

#include <QLabel>
#include <QMap>
#include <QThread>
#include <QProgressBar>

class AEDController : public QObject
{
    Q_OBJECT

public:
    // Constructor
    AEDController(QObject* parent = nullptr);

    // Destructor
    ~AEDController();

    bool setStage(Stage s); // Change's the AED System's stage
    void changeMainstage(Stage s); // Updates the mainStage's value in the system

    void addShock(); // Adds a shock

    // Set/Check system statuses
    void setSystemFault(bool fault);
    void setPowerCapacity(int capacity);
    void setShockCount(int num);
    void setPower(bool p);
    bool isSystemFault();
    bool isLowBattery();
    bool isOn();

    QAEDScreen* getScreen(); 
    Pads* getPads();
    StageManager* getStage(Stage s);
    Stage getCurrentStage();
    QIconButton* getPowerButton();
    QIconButton* getPediatricButton();
    QLabel* getPowerIndicator();
    QLabel* getPediatricIndicator();
    QIconButton* getStageButton(int i);
    QLabel* getStageLabel(int i);

    QProgressBar* getBatteryBar();

    void on();
    void off();

private:
    // The current stage the system is at
    Stage mainStage;

    // Screen
    QAEDScreen* screen;
    QThread* screenThread;
    Pads* pads;

    // Stages Managers
    QMap<Stage, StageManager*> stages;
    QMap<Stage, QThread*> stageThreads;

    QIconButton* powerButton;
    QIconButton* pediatricButton;
    QLabel* powerIndicator;
    QLabel* pediatricIndicator;
    QList<QIconButton*> stageButtons;
    QList<QLabel*> stageLabels;

    QProgressBar* batteryLevel;

    bool systemFault;
    int powerCapacity;
    int numShocks;
    bool power;
};

#endif // AEDCONTROLLER_H