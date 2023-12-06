#ifndef STAGE2MANAGER_H
#define STAGE2MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage2Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage2Manager(AEDController *controller, QObject *parent = nullptr);


private:
    AEDController *controller;
};

#endif // STAGE2MANAGER_H