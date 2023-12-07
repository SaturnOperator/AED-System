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

    virtual bool activate() = 0; // Abstract class to be implemented later
    virtual bool nextStage() = 0; // Abstract class to be implemented later

    bool isComplete() const; // returns true if stage is complete
    bool isError() const; // returns true if stage is in an error state

    bool setStatus(int s); // Changes the status of the stage
    int getStatusCode() const; // Returns stage's status as an int


protected:
    AEDController* controller;
    QAEDScreen* screen;
    Stage stage;
    int status;
};

#endif // STAGEMANAGER_H