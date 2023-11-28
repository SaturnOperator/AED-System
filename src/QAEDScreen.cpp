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

void QAEDScreen::setStage(Stage stage){
    this->stage = stage;
    clearAll();
    switch (stage) {
    case Stage::POWER:
        // @@ Needs Impl.
        break;
    case Stage::PADS:
        stage2Pads();
        break;
    case Stage::ANALYZE:
        stage3Analyze();
        break;
    case Stage::SHOCK:
        // @@ Needs Impl.
        break;
    case Stage::CPR:
        stage5Cpr();
        break;
    case Stage::POST_USE:
        // @@ Needs Impl.
        break;
    }
    refresh();
}

void QAEDScreen::stage2Pads(){

    QStringList stage2Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_2_chest", 
        "_2_chest_msg_expose_chest", 
        "_2_chest_pads_indicator", 
        "_2_pads", 
        "_2_pads_msg_attach_pads", 
    };

    for (const QString &str : stage2Elements) {
        showElementId(str, true);
    }
    refresh();
}

void QAEDScreen::stage5Cpr(){

    QStringList stage5Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_5_sleepy", 
        "_5a_cpr", 
        "_5a_cpr_depth_0", 
        "_5a_cpr_depth_1", 
        "_5a_cpr_depth_10", 
        "_5a_cpr_depth_2", 
        "_5a_cpr_depth_3", 
        "_5a_cpr_depth_4", 
        "_5a_cpr_depth_5", 
        "_5a_cpr_depth_6", 
        "_5a_cpr_depth_7", 
        "_5a_cpr_depth_8", 
        "_5a_cpr_depth_9", 
        "_5a_cpr_msg_good_comp", 
        "_5a_cpr_msg_push_harder", 
        "_5a_cpr_msg_start_cpr", 
        "_5a_cpr_msg_stop_cpr", 
        "_5a_cpr_time",
    };

    for (const QString &str : stage5Elements) {
        showElementId(str, true);
    }
    refresh();
}

void QAEDScreen::stage3Analyze(){

    QStringList stage3Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_3a_sleepy", 
        "_3a_stand_back", 
        "_3a_stand_msg_analyzing", 
        "_3a_stand_msg_dont_touch", 
        "_3a_stand_msg_stand_back", 
    };

    for (const QString &str : stage3Elements) {
        showElementId(str, true);
    }
    refresh();
}