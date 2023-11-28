#ifndef QAEDSCREEN_H
#define QAEDSCREEN_H

#include "defs.h"
#include "QSvgWidget.h"

class QAEDScreen : public QSvgWidget {
    Q_OBJECT

public:
    explicit QAEDScreen(QWidget *parent = nullptr);

    void setStage(Stage stage);

private:
    Stage stage;
    // Additional methods and properties for QAEDScreen can be declared here
};

#endif // QAEDSCREEN_H