#ifndef STAGE5_H
#define STAGE5_H

#include "StageManager.h"

#include <QTimer>

class Stage5 : public StageManager {
    Q_OBJECT

public:
    explicit Stage5(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage5CPR s); // Overload setStatus(int status)

    bool setDepth(int d);

private:
    QTimer* timer;

    const int interval = 500; // 0.5 seconds per internal -- set to 500 for 120 BPM, 600 for 100 BPM
    int intervalCount; // Perform actions based on the interval count
    int maxTicks; // CPR ends when this amount is reached, needs to be calculated

    int depth; // Sensor reading from pads
    int lastDepth;
    int idleCount; // Keeps track of how long CPR hasn't been pursued
    int timeCount;

    bool cprIndicator;

    void checkCompression();
    
    // Checks depth, updates screen, show messages and keep track of timing
    // This method runs every interval (0.5s) and updates the system accordingly
    void step();

};

#endif // STAGE5_H