#ifndef AEDCONTROLLER_H
#define AEDCONTROLLER_H

#include "defs.h"
#include "aed_stages.h"

#include "QAEDScreen.h"

#include <QThread>

class AEDController : public QObject
{
    Q_OBJECT

public:
    // Constructor
    AEDController(QObject* parent = nullptr);

    // Destructor
    ~AEDController();

private:
    // The current stage the system is at
    Stage mainStage;

    // The status of each stage, these can affect the main at time
    Stage1Power substage1;
    Stage2Install substage2;
    Stage3Analyze substage3;
    Stage4Shock substage4;
    Stage5CPR substage5;
    Stage6PostUse substage6;

    // Screen
    QAEDScreen* screen;
    QThread* screenThread;
    
};

#endif // AEDCONTROLLER_H