#ifndef STAGE3_H
#define STAGE3_H

#include <QTimer>

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
    QTimer* timer;
    int ecgPercent;

    int stepCount;

    void step();

};

#endif // STAGE3_H