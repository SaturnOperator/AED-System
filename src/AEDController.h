#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H

#include "defs.h"
#include "aed_stages.h"

#include "QAEDScreen.h"
#include "StageManager.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"
#include "Stage5.h"
#include "Stage6.h"

#include <QMap>

#include <QThread>

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

    QAEDScreen* getScreen(); 
    StageManager* getStage(Stage s);
    Stage getCurrentStage();

private:
    // The current stage the system is at
    Stage mainStage;

    // Screen
    QAEDScreen* screen;
    QThread* screenThread;

    // Stages Managers
    QMap<Stage, StageManager*> stages;
    QMap<Stage, QThread*> stageThreads;    
};

#endif // AEDCONTROLLER_H