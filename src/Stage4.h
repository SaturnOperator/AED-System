#ifndef STAGE4_H
#define STAGE4_H

#include "StageManager.h"

class Stage4 : public StageManager {
    Q_OBJECT

public:
    explicit Stage4(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE4_H