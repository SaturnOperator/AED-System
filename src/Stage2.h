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
    const int interval = 500; // 0.5 seconds per internal -- set to 500 for 120 BPM, 600 for 100 BPM
    int intervalCount; // Perform actions based on the interval count

    bool init; // Don't show attach pads error on init, only show it if disconnects mid operation
    bool adultLocal; // used to compare current val to pads
    bool showPediatricOption; // flag set once the pediatric option button is show
    int pediatricOptionTime; // After showing button end stage after x time

    void step();
    bool checkSafetySystems(); // Checks pads connection and attachment to patient
};

#endif // STAGE2_H
