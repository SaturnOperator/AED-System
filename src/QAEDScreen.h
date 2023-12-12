#ifndef QAEDSCREEN_H
#define QAEDSCREEN_H

#include "defs.h"

#include "QSvgWidget.h"

#include <QStringList>
#include <QTimer>
#include <QTime>

class QAEDScreen : public QSvgWidget {
    Q_OBJECT

public:
    explicit QAEDScreen(QWidget *parent = nullptr);

    ~QAEDScreen();

    void startCountdown(); // Start/Reset CPR countdown timer
    void stopCountdown(); // Stop CPR timer

    void clearAll();
    
    void setStage(Stage stage); // Switch screen to this stage using these functions
    void updateTime(); // Add one second to elapsed time;
    void setShockCount(int i); // Set shock count

    /* Stage 1 (Power On) methods */
    bool showMsg1UnitOk(bool show);
    bool showMsg1LowBat(bool show);
    bool showMsg1SysFault(bool show);
    bool showMsg1NoPads(bool show);
    void clearMsg1(); 
    bool showInstruction1(int index); // 0 is none, 1-5 selects instr 1-5

    /* Stage 2 (Install Pads) methods */
    bool showStage2aChest(bool show);
    bool showStage2aPadsIndicator(bool show); // Show little indicators on to where to put the pads
    bool showStage2aPads(bool show); // Show pads on the patient's chest
    bool showMsg2aExposeChest(bool show);
    bool showMsg2aAttachPads(bool show);
    bool showMsg2aPluginPads(bool show);
    void clearMsg2a(); // Hide all Stage 2 messages
    void hideStage2a();
    void hideStage2b();
    bool showStage2bChildPatient(); // Show child patient option
    bool showStage2bToggleChildPatient(bool show); // Toggle adult/child patient

    /* Stage 3 (Analyzing) methods */
    bool showMsg3aAnalyzing(bool show);
    bool showMsg3aDontTouch(bool show);
    bool showMsg3aStandBack(bool show);
    void clearMsg3a();
    // ECG functions
    void stage3bECG();
    bool showLabel3bSinus(bool show);
    bool showLabel3bVF(bool show);
    bool showLabel3bVT(bool show);
    bool showLabel3bAsystole(bool show);
    void clearLabel3b();
    bool showRhythm(int rhythm);
    void setBpm(int bpm);
    bool sweepEcg(int rIndex, int percent); // Shows that much % of the ECG graph, used to animate

    /* Stage 4 (Shock) methods */
    bool shockProgress(int level); // 0 is cleared, 10 is max
    bool showMsg4Shock(bool show);
    bool showMsg4ShockDelivered(bool show);
    bool showMsg4DontTouch(bool show);
    bool showMsg4NoShock(bool show);
    void clearMsg4();

    /* Stage 5 (CPR) methods */
    bool setStage5CompressionLevel(int level);
    bool showStage5CPRIndicator(bool show);
    bool showMsg5GoodCompression(bool show);
    bool showMsg5PushHarder(bool show);
    bool showMsg5StartCpr(bool show);
    bool showMsg5StopCpr(bool show);
    void clearMsg5(); // Hide all Stage 5 messages

private:
    Stage stage;
    QDomElement* timeText;
    QDomElement* shocksText;
    QDomElement* countdownText;
    QDomElement* bpmText;

    // Elapsed time
    QTimer* timer;
    QTime startTime;

    QTime countdownTime;
    bool countdownActive;

    bool showVerifyStage(Stage s, QString msgId, bool show);
    void stage1(); // Power on
    void stage2(); // Install Pads
    void stage3(); // Analyzing heart rhythm
    void stage4(); // Shock
    void stage5(); // CPR

    void hideStage3a(); 


};

#endif // QAEDSCREEN_H