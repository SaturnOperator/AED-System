#ifndef STAGE6_H
#define STAGE6_H

#include "StageManager.h"

class AEDController; // Forward declare

class Stage6 : public StageManager {
    Q_OBJECT

public:
    explicit Stage6(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE6_H