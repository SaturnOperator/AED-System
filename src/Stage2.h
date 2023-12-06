#ifndef STAGE2_H
#define STAGE2_H

#include "StageManager.h"

class Stage2 : public StageManager {
    Q_OBJECT

public:
    explicit Stage2(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE2_H