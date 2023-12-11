#ifndef STAGE3_H
#define STAGE3_H

#include <QRandomGenerator>

#include "StageManager.h"

class Stage3 : public StageManager {
    Q_OBJECT

public:
    explicit Stage3(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage3Analyze s); // Overload setStatus(int status)

private:
    int ecgPercent;
    int rIndex;

    int stepCount;

    void step();
    int getECGRhythmIndex(Rhythms r);

};

#endif // STAGE3_H