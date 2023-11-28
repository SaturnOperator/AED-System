#ifndef QAEDSCREEN_H
#define QAEDSCREEN_H

#include "defs.h"

#include "QSvgWidget.h"

#include <QStringList>
class QAEDScreen : public QSvgWidget {
    Q_OBJECT

public:
    explicit QAEDScreen(QWidget *parent = nullptr);

    void clearAll();
    
    void setStage(Stage stage); // Switch screen to this stage using these functions
        
    /* Stage 5 (CPR) methods */
    bool setCompressionLevel(int level);
    bool showMsg5GoodCompression(bool show);
    bool showMsg5PushHarder(bool show);
    bool showMsg5StartCpr(bool show);
    bool showMsg5StopCpr(bool show);

private:
    Stage stage;

    bool showMessage(Stage s, QString msgId, bool show);
    void stage1(); // Power on
    void stage2(); // Install Pads
    void stage3(); // Analyzing heart rhythm
    void stage4(); // Shock
    void stage5(); // CPR

};

#endif // QAEDSCREEN_H