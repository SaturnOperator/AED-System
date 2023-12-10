#ifndef STAGE2_H
#define STAGE2_H

#include "StageManager.h"

class Stage2 : public StageManager {
    Q_OBJECT

public:
    explicit Stage2(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage2Install s); // Overload setStatus(int status)

private:
    QTimer* timer;

    const int interval = 500; // 0.5 seconds per internal -- set to 500 for 120 BPM, 600 for 100 BPM
    int intervalCount; // Perform actions based on the interval count
    void step();
};

#endif // STAGE2_H
