#ifndef STAGE1MANAGER_H
#define STAGE1MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage1Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage1Manager(AEDController *controller, QObject *parent = nullptr);


private:
    AEDController* controller;
};

#endif // STAGE1MANAGER_H