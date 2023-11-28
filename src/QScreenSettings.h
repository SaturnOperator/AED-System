#ifndef QSCREENSETTINGS_H
#define QSCREENSETTINGS_H

#include "defs.h"
#include "QAEDScreen.h"

#include <QTabWidget>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>

class QScreenSettings : public QTabWidget {
    Q_OBJECT

public:
    QScreenSettings(QAEDScreen* aedScreen, QWidget *parent = nullptr);
    ~QScreenSettings();

    void setStage(Stage stage);

private:
    QAEDScreen* screen;

    void stage5Init();

};

#endif // QSCREENSETTINGS_H
