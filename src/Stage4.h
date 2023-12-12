#ifndef STAGE4_H
#define STAGE4_H

#include "StageManager.h"

class Stage4 : public StageManager {
    Q_OBJECT

public:
    explicit Stage4(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage4Shock s); // Overload setStatus(int status)

private:
    const int interval = 333; // 0.5 sec intervals
    int intervalCount;
    bool shocked;

    void step();
    bool checkShockableRhythm();
};

#endif // STAGE4_H