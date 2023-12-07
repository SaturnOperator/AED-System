#ifndef STAGE1_H
#define STAGE1_H

#include "StageManager.h"

class Stage1 : public StageManager {
    Q_OBJECT

public:
    explicit Stage1(AEDController* controller, QObject *parent = nullptr);

    bool start();
    void stop();
    bool nextStage();
    bool setStatus(Stage1Power s); // Overload setStatus(int status)

private:
    Stage1Power status;

};

#endif // STAGE1_H