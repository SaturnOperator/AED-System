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
    

    /* Stage 2 (Install Pads) methods */
    bool showStage2PadsIndicator(bool show); // Show little indicators on to where to put the pads
    bool showStage2Pads(bool show); // Show pads on the patient's chest
    bool showMsg2ExposeChest(bool show);
    bool showMsg2AttachPads(bool show);
    void clearMsg2(); // Hide all Stage 2 messages

    /* Stage 3 (Analyzing) methods */
    bool showMsg3Analyzing(bool show);
    bool showMsg3DontTouch(bool show);
    bool showMsg3StandBack(bool show);
    void clearMsg3();

    /* Stage 5 (CPR) methods */
    bool setStage5CompressionLevel(int level);
    bool showMsg5GoodCompression(bool show);
    bool showMsg5PushHarder(bool show);
    bool showMsg5StartCpr(bool show);
    bool showMsg5StopCpr(bool show);
    void clearMsg5(); // Hide all Stage 5 messages

private:
    Stage stage;

    bool showVerifyStage(Stage s, QString msgId, bool show);
    void stage1(); // Power on
    void stage2(); // Install Pads
    void stage3(); // Analyzing heart rhythm
    void stage4(); // Shock
    void stage5(); // CPR

};

#endif // QAEDSCREEN_H