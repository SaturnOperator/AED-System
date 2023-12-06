#ifndef STAGE5_H
#define STAGE5_H

#include "StageManager.h"

class Stage5 : public StageManager {
    Q_OBJECT

public:
    explicit Stage5(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE5_H