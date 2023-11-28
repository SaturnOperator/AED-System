#ifndef QAEDSCREEN_H
#define QAEDSCREEN_H

#include "defs.h"

#include "QSvgWidget.h"
#include <QStringList>

class QAEDScreen : public QSvgWidget {
    Q_OBJECT

public:
    explicit QAEDScreen(QWidget *parent = nullptr);

    void setStage(Stage stage);
    void clearAll();

private:
    Stage stage;
    void stage2Pads();
    void stage3Analyze();
    void stage5Cpr();
    // Additional methods and properties for QAEDScreen can be declared here
};

#endif // QAEDSCREEN_H