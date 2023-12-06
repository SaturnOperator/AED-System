#ifndef STAGE3MANAGER_H
#define STAGE3MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage3Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage3Manager(AEDController *controller, QObject *parent = nullptr);


private:
    AEDController *controller;
};

#endif // STAGE3MANAGER_H