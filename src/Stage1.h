#ifndef STAGE1_H
#define STAGE1_H

#include "StageManager.h"

class Stage1 : public StageManager {
    Q_OBJECT

public:
    explicit Stage1(AEDController* controller, QObject *parent = nullptr);

private:

};

#endif // STAGE1_H