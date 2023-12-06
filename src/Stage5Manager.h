#ifndef STAGE5MANAGER_H
#define STAGE5MANAGER_H

#include <QObject>
#include "AEDController.h"

class Stage5Manager : public QObject {
    Q_OBJECT

public:
    explicit Stage5Manager(AEDController *controller, QObject *parent = nullptr);


private:
    AEDController *controller;
};

#endif // STAGE5MANAGER_H