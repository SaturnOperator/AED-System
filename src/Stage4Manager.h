#ifndef STAGE4MANAGER_H
#define STAGE4MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage4Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage4Manager(AEDController *controller, QObject *parent = nullptr);


private:
    AEDController *controller;
};

#endif // STAGE4MANAGER_H