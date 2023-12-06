#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QObject>

#include "defs.h"

#include "QAEDScreen.h"

class AEDController; // Forward declare

class StageManager : public QObject {
    Q_OBJECT

public:
    explicit StageManager(Stage s, AEDController* controller, QObject *parent = nullptr);

protected:
    AEDController* controller;
    QAEDScreen* screen;
    Stage stage;
};

#endif // STAGEMANAGER_H