#ifndef STAGE3_H
#define STAGE3_H

#include "StageManager.h"

class Stage3 : public StageManager {
    Q_OBJECT

public:
    explicit Stage3(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE3_H