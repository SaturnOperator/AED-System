#ifndef STAGE6MANAGER_H
#define STAGE6MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage6Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage6Manager(AEDController *controller, QObject *parent = nullptr);

private:
    AEDController *controller;
};

#endif // STAGE6MANAGER_H