#include "QAEDScreen.h"

QAEDScreen::QAEDScreen(QWidget *parent)
    : QSvgWidget("./screen.svg", parent) {

    setStyleSheet("border-radius: 10px;");

    clearAll(); // Start in CPR stage
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

// General function to show message
// Only shows the message if the current stage is the one where the message can appear
bool QAEDScreen::showMessage(Stage s, QString msgId, bool show){
    if(stage != s){
        return false;
    }

    showElementId(msgId, show);
    refresh();
    return true;
}

/* STAGE 1 (Power) Functions */

// Switch to the Stage 1 screen
// void QAEDScreen::stage1(){
//
// }

/* STAGE 2 (Power) Functions */

// Switch to the Stage 2 screen
// void QAEDScreen::stage2(){
//
// }

// Switch to the Stage 2 screen
void QAEDScreen::stage2(){

    QStringList stage2Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_2_chest", 
        "_2_chest_msg_expose_chest", 
        "_2_chest_pads_indicator", 
        "_2_pads", 
        // "_2_pads_msg_attach_pads", 
    };

    for (const QString &str : stage2Elements) {
        showElementId(str, true);
    }
    refresh();
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
bool QAEDScreen::setCompressionLevel(int level){
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
        qFatal() << "QAEDScreen::setCompressionLevel() Level must be between 0-11.";
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
    // Disable the rest of the stage 5 messages
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false);        
    return showMessage(Stage::CPR, "_5a_cpr_msg_good_comp", show);
}

bool QAEDScreen::showMsg5PushHarder(bool show){
    // Disable the rest of the stage 5 messages
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false); 
    return showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", show);
}

bool QAEDScreen::showMsg5StartCpr(bool show){
    // Disable the rest of the stage 5 messages
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_stop_cpr", false); 
    return showMessage(Stage::CPR, "_5a_cpr_msg_start_cpr", show);
}

bool QAEDScreen::showMsg5StopCpr(bool show){
    // Disable the rest of the stage 5 messages
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_push_harder", false);
    showMessage(Stage::CPR, "_5a_cpr_msg_start_cpr", false);
    return showMessage(Stage::CPR, "_5a_cpr_msg_stop_cpr", show);
}
