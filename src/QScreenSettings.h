#ifndef QSCREENSETTINGS_H
#define QSCREENSETTINGS_H

#include "defs.h"
#include "AEDController.h"

#include <QTabWidget>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include <QPushButton>

class QScreenSettings : public QTabWidget {
    Q_OBJECT

public:
    QScreenSettings(AEDController* controller, QWidget *parent = nullptr);
    ~QScreenSettings();

    void setStage(Stage stage);

private:
    AEDController* controller;

    // Create settings tab for each stage/screen panel
    void stage1Init();
    void stage2Init();
    void stage3Init();
    void stage4Init();
    void stage5Init();
    void stage6Init();
};

#endif // QSCREENSETTINGS_H
