#include "QAEDScreen.h"


QAEDScreen::QAEDScreen(QWidget *parent)
    : QSvgWidget("./screen.svg", parent), shockCount(0) {

    setStyleSheet("border-radius: 10px;");
    clearAll(); // Clear screen

    // Set up elements that have replacable text
    timeDisplay = getElement("_0_time");
    shocksDisplay = getElement("_0_shocks_number");
    countdownDisplay = getElement("_5a_cpr_time");

    addShock(); // Start shock count 0

    // Create a timer to update screen every second for the elapsed time, and CPR countdown
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QAEDScreen::updateTime);
    timer->start(1000); // Update every second
    startTime = QTime::currentTime();

    // Start CPR countdown timer
    startCountdown();
}

QAEDScreen::~QAEDScreen(){
    delete timer;
}

void QAEDScreen::startCountdown(){
    countdownTime = QTime::currentTime();
    countdownActive = true;
}

void QAEDScreen::stopCountdown(){
    countdownActive = false;
    qInfo() << "Stop CPR";
}

void QAEDScreen::clearAll(){
    // Hide everything
    for(QDomElement* e : elements){
        showElement(e, false);
    }
    showElementId("background", true);
    refresh();
}

// Switch to the Stage screen by passing in Stage enum
void QAEDScreen::setStage(Stage stage){
    this->stage = stage;
    clearAll();
    switch (stage) {
    case Stage::POWER:
        // @@ Needs Impl.
        break;
    case Stage::PADS:
        stage2();
        break;
    case Stage::ANALYZE:
        stage3();
        break;
    case Stage::SHOCK:
        // @@ Needs Impl.
        break;
    case Stage::CPR:
        stage5();
        break;
    case Stage::POST_USE:
        // @@ Needs Impl.
        break;
    }
    refresh();
}

// Only show element if the current stage is the one where the message can appear
bool QAEDScreen::showVerifyStage(Stage s, QString id, bool show){
    if(stage != s){
        return false;
    }

    showElementId(id, show);
    refresh();
    return true;
}

/* STAGE 1 (Power) Functions */

// Switch to the Stage 1 screen
// void QAEDScreen::stage1(){
//
// }

/* STAGE 2 (Install Pads) Functions */

// Switch to the Stage 2 screen
void QAEDScreen::stage2(){

    QStringList stage2Elements = {
        // "_0_shocks_label", 
        // "_0_shocks_number", 
        "_0_time",
        "_2_chest",
        // "_2_chest_pads_indicator", 
        // "_2_pads",
        // "_2_chest_msg_expose_chest",
        // "_2_pads_msg_attach_pads",
    };

    for (const QString &str : stage2Elements) {
        showElementId(str, true);
    }
    refresh();
}

// Show little indicators on to where to put the pads
bool QAEDScreen::showStage2PadsIndicator(bool show){
    return showVerifyStage(Stage::PADS, "_2_chest_pads_indicator", show);
}

// Show pads on the patient's chest
bool QAEDScreen::showStage2Pads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2_chest_msg_expose_chest", false); // Hide expose chest message
    }
    return showVerifyStage(Stage::PADS, "_2_pads", show);
}

// Show various messages for stage 2 (Install Pads)
bool QAEDScreen::showMsg2ExposeChest(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2_pads_msg_attach_pads", false);  
    }
    return showVerifyStage(Stage::PADS, "_2_chest_msg_expose_chest", show);
}

bool QAEDScreen::showMsg2AttachPads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2_chest_msg_expose_chest", false);  
    }
    return showVerifyStage(Stage::PADS, "_2_pads_msg_attach_pads", show);
}

void QAEDScreen::clearMsg2(){ // Hide all Stage 2 messages
    showVerifyStage(Stage::PADS, "_2_chest_msg_expose_chest", false);
    showVerifyStage(Stage::PADS, "_2_pads_msg_attach_pads", false);
}

/* STAGE 3 (Analyze) Functions */

// Switch to the Stage 3 screen
void QAEDScreen::stage3(){

    QStringList stage3Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_3a_sleepy", 
        "_3a_stand_back", 
        // "_3a_stand_msg_analyzing", 
        // "_3a_stand_msg_dont_touch", 
        // "_3a_stand_msg_stand_back", 
    };

    for (const QString &str : stage3Elements) {
        showElementId(str, true);
    }
    refresh();
}

// Show various messages for stage 3 (Analyzing)
bool QAEDScreen::showMsg3Analyzing(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", show);
}

bool QAEDScreen::showMsg3DontTouch(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", show);
}

bool QAEDScreen::showMsg3StandBack(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", show);
}

void QAEDScreen::clearMsg3(){
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
}

/* STAGE 4 (Shock) Functions */

// Switch to the Stage 4 screen
// void QAEDScreen::stage4(){
//
// }

/* STAGE 5 (CPR) Functions */

// Switch to the Stage 5 screen
void QAEDScreen::stage5(){

    QStringList stage5Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_5_sleepy", 
        "_5a_cpr", 
        "_5a_cpr_time",
        // "_5a_cpr_depth_0", 
        // "_5a_cpr_depth_1", 
        // "_5a_cpr_depth_2", 
        // "_5a_cpr_depth_3", 
        // "_5a_cpr_depth_4", 
        // "_5a_cpr_depth_5", 
        // "_5a_cpr_depth_6", 
        // "_5a_cpr_depth_7", 
        // "_5a_cpr_depth_8", 
        // "_5a_cpr_depth_9", 
        // "_5a_cpr_depth_10", 
        // "_5a_cpr_msg_good_comp", 
        // "_5a_cpr_msg_push_harder", 
        // "_5a_cpr_msg_start_cpr", 
        // "_5a_cpr_msg_stop_cpr", 
    };

    for (const QString &str : stage5Elements) {
        showElementId(str, true);
    }
    refresh();
}

// Updates the depth compression level, takes int values 0-11
//  0:   being the minimum amount (no compression)
//  11:  being the maximum amount (full compression)
bool QAEDScreen::setStage5CompressionLevel(int level){
    if(stage != Stage::CPR){
        return false; // Don't make changes if not in the CPR stage
    }

    QStringList compressionLevelBar = {
        "_5a_cpr_depth_0", 
        "_5a_cpr_depth_1", 
        "_5a_cpr_depth_2", 
        "_5a_cpr_depth_3", 
        "_5a_cpr_depth_4", 
        "_5a_cpr_depth_5", 
        "_5a_cpr_depth_6", 
        "_5a_cpr_depth_7", 
        "_5a_cpr_depth_8", 
        "_5a_cpr_depth_9", 
        "_5a_cpr_depth_10",
    };

    if(level < 0 || level > compressionLevelBar.size()){
        qInfo() << "QAEDScreen::setCompressionLevel() Level must be between 0-11.";
        return false;
    }

    // Show up to the level
    for (int i = 0; i < level; ++i){
        showElementId(compressionLevelBar[i], true);
    }

    // Hide the rest
    for (int i = level; i < compressionLevelBar.size(); ++i){
        showElementId(compressionLevelBar[i], false);
    }

    // updates changes
    refresh();
    return true;
}

// Show various messages for stage 5 (CPR screen)
bool QAEDScreen::showMsg5GoodCompression(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false);        
    }
    return showVerifyStage(Stage::CPR, "_5a_cpr_msg_good_comp", show);
}

bool QAEDScreen::showMsg5PushHarder(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_good_comp", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false); 
    }
    return showVerifyStage(Stage::CPR, "_5a_cpr_msg_push_harder", show);
}

bool QAEDScreen::showMsg5StartCpr(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_good_comp", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false); 
    }
    return showVerifyStage(Stage::CPR, "_5a_cpr_msg_start_cpr", show);
}

bool QAEDScreen::showMsg5StopCpr(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_good_comp", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
        showVerifyStage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
    }
    return showVerifyStage(Stage::CPR, "_5a_cpr_msg_stop_cpr", show);
}

void QAEDScreen::clearMsg5(){ // Hide all Stage 5 messages
    showVerifyStage(Stage::CPR, "_5a_cpr_msg_good_comp", false);
    showVerifyStage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showVerifyStage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
    showVerifyStage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false);
}

void QAEDScreen::updateTime(){
    // Calculate elapsed time
    int elapsedSeconds = startTime.secsTo(QTime::currentTime());
    int minutes = elapsedSeconds / 60;
    int seconds = elapsedSeconds % 60;

    QString formattedTime = QString("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));

    // Update elapsed time
    changeText(timeDisplay, formattedTime);

    // Calculate CPR countdown
    if (countdownActive) {
        int countdownElapsed = countdownTime.secsTo(QTime::currentTime());
        int countdown = qMax(0, CPR_COUNTDOWN_DURATION - countdownElapsed);

        if(countdown == 0){
            stopCountdown();
        }

        int minutesRemaining = countdown / 60;
        int secondsRemaining = countdown % 60;
        QString countdownFormatted = QString("%1:%2")
            .arg(minutesRemaining, 2, 10, QChar('0'))
            .arg(secondsRemaining, 2, 10, QChar('0'));

        // Update countdown timer
        changeText(countdownDisplay, countdownFormatted);
    }
}

void QAEDScreen::addShock(){
    changeText(shocksDisplay, QString("%1").arg(shockCount++, 2, 10, QChar('0')));
}