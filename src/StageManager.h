#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <QObject>

#include "defs.h"

#include "Pads.h"
#include "QAEDScreen.h"

class AEDController; // Forward declare

class StageManager : public QObject {
    Q_OBJECT

public:
    explicit StageManager(Stage s, AEDController* controller, QObject *parent = nullptr);

    virtual bool start() = 0; // Abstract class to be implemented later
    virtual void stop() = 0; // Abstract class to be implemented later
    virtual bool nextStage() = 0; // Abstract class to be implemented later

    bool isDone() const; // Returns true if stage is complete
    bool isActive() const; // Return true if status code > 0 
    bool isIdle() const; // Returns if stage is in Idle status
    bool isError() const; // Returns true if stage is in an error state

    bool setStatus(int s); // Changes the status of the stage
    int getStatusCode() const; // Returns stage's status as an int


protected:
    AEDController* controller;
    QAEDScreen* screen;
    Pads* pads;
    Stage stage;
    int status;

    // virtual bool checkSafetySystems();
};

#endif // STAGEMANAGER_H