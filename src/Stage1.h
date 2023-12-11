#ifndef STAGE1_H
#define STAGE1_H

#include "StageManager.h"
#include <QTimer>

class Stage1 : public StageManager {
    Q_OBJECT

public:
    explicit Stage1(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage1Power s); // Overload setStatus(int status)

    bool setInstruction(int i);

private:
    Stage1Power status;

    QTimer* timer;
    
    const int interval = 3000; // 3 seconds per interval
    int intervalCount; // Perform actions based on the interval count
    int maxTicks; // Power on sequence ends when this amount is reached, needs to be calculated

    int instructionNum;
    int instruction;

    bool power;
    
    void step();

};

#endif // STAGE1_H