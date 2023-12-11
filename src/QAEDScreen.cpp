#include "QAEDScreen.h"


QAEDScreen::QAEDScreen(QWidget *parent)
    : QSvgWidget("./screen.svg", parent), shockCount(0) {

    setStyleSheet("border-radius: 10px;");
    clearAll(); // Clear screen

    // Set up elements that have replacable text
    timeText = getElement("_0_time");
    shocksText = getElement("_0_shocks_number");
    countdownText = getElement("_5a_cpr_time");
    bpmText = getElement("_3b_bpm");

    // Create a timer to update screen every second for the elapsed time, and CPR countdown
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &QAEDScreen::updateTime);
    timer->start(1000); // Update every second
    startTime = QTime::currentTime();
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
        stage1();
        break;
    case Stage::PADS:
        stage2();
        break;
    case Stage::ANALYZE:
        stage3();
        break;
    case Stage::SHOCK:
        stage4();
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
void QAEDScreen::stage1(){

    QStringList stage1Elements = {
        // "_0_shocks_label", 
        // "_0_shocks_number", 
        "_0_time",
        "_1a_step1",
        "_1a_step2",
        "_1a_step3",
        "_1a_step4",
        "_1a_step5",
    };

    for (const QString &str : stage1Elements) {
        showElementId(str, true);
    }
    refresh();
}

bool QAEDScreen::showMsg1UnitOk(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::POWER, "_1a_msg_low_battery", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_system_fault", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_no_pads", false);  
    }
    return showVerifyStage(Stage::POWER, "_1a_msg_unit_ok", show);
}

bool QAEDScreen::showMsg1LowBat(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::POWER, "_1a_msg_unit_ok", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_system_fault", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_no_pads", false);  
    }
    return showVerifyStage(Stage::POWER, "_1a_msg_low_battery", show);
}

bool QAEDScreen::showMsg1SysFault(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::POWER, "_1a_msg_unit_ok", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_low_battery", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_no_pads", false);  
    }
    return showVerifyStage(Stage::POWER, "_1a_msg_system_fault", show);
}

bool QAEDScreen::showMsg1NoPads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::POWER, "_1a_msg_unit_ok", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_low_battery", false);  
        showVerifyStage(Stage::POWER, "_1a_msg_system_fault", false);  
    }
    return showVerifyStage(Stage::POWER, "_1a_msg_no_pads", show);
}

void QAEDScreen::clearMsg1(){ // Hide all Stage 1 messages
    showVerifyStage(Stage::POWER, "_1a_msg_unit_ok", false);
    showVerifyStage(Stage::POWER, "_1a_msg_low_battery", false);
    showVerifyStage(Stage::POWER, "_1a_msg_system_fault", false);
    showVerifyStage(Stage::POWER, "_1a_msg_no_pads", false);
}

bool QAEDScreen::showInstruction1(int index){
    if(stage != Stage::POWER){
        return false;
    }

    // Index 0 clears the highlighted step
    // Index 1-5 selects one of the ones below
    QStringList instructions = {
        "_1a_step1_active",
        "_1a_step2_active",
        "_1a_step3_active",
        "_1a_step4_active",
        "_1a_step5_active",
    };

    if(index < 0 || index > instructions.length()){
        qInfo() << "QAEDScreen::showInstruction1 ERROR: OOB, max = " << instructions.length()-1;
        return false;
    }

    for (int i = 1; i <= instructions.length(); i++){
        showElementId(instructions[i-1], i==index);
    }
    refresh();
    return true;
}

/* STAGE 2 (Install Pads) Functions */

// Switch to the Stage 2 screen
void QAEDScreen::stage2(){

    QStringList stage2aElements = {
        // "_0_shocks_label", 
        // "_0_shocks_number", 
        "_0_time",
        // "_2a_chest",
        // "_2a_chest_pads_indicator", 
        // "_2a_pads",
        // "_2a_chest_msg_expose_chest",
        // "_2a_pads_msg_attach_pads",
    };

    for (const QString &str : stage2aElements) {
        showElementId(str, true);
    }
    refresh();
}

// Show chest
bool QAEDScreen::showStage2aChest(bool show){
    return showVerifyStage(Stage::PADS, "_2a_chest", show);
}

// Show little indicators on to where to put the pads
bool QAEDScreen::showStage2aPadsIndicator(bool show){
    return showVerifyStage(Stage::PADS, "_2a_chest_pads_indicator", show);
}

// Show pads on the patient's chest
bool QAEDScreen::showStage2aPads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2a_chest_msg_expose_chest", false); // Hide expose chest message
    }
    return showVerifyStage(Stage::PADS, "_2a_pads", show);
}

// Show various messages for stage 2 (Install Pads)
bool QAEDScreen::showMsg2aExposeChest(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2a_pads_msg_attach_pads", false);
        showVerifyStage(Stage::PADS, "_2a_pads_msg_plug_in_pads", false); 
    }
    return showVerifyStage(Stage::PADS, "_2a_chest_msg_expose_chest", show);
}

bool QAEDScreen::showMsg2aAttachPads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2a_chest_msg_expose_chest", false);
        showVerifyStage(Stage::PADS, "_2a_pads_msg_plug_in_pads", false);  
    }
    return showVerifyStage(Stage::PADS, "_2a_pads_msg_attach_pads", show);
}

bool QAEDScreen::showMsg2aPluginPads(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::PADS, "_2a_chest_msg_expose_chest", false);
        showVerifyStage(Stage::PADS, "_2a_pads_msg_attach_pads", false);    
    }
    return showVerifyStage(Stage::PADS, "_2a_pads_msg_plug_in_pads", show);
}

void QAEDScreen::clearMsg2a(){ // Hide all Stage 2 messages
    showVerifyStage(Stage::PADS, "_2a_chest_msg_expose_chest", false);
    showVerifyStage(Stage::PADS, "_2a_pads_msg_attach_pads", false);
    showVerifyStage(Stage::PADS, "_2a_pads_msg_plug_in_pads", false);
}

void QAEDScreen::hideStage2a(){
    // Hide these elemnents
    QStringList stage2aElements = {
        "_2a_chest",
        "_2a_chest_pads_indicator", 
        "_2a_pads",
        "_2a_chest_msg_expose_chest",
        "_2a_pads_msg_attach_pads",
        "_2a_pads_msg_plug_in_pads"
    };

    for (const QString &str : stage2aElements) {
        showElementId(str, false);
    }
}


void QAEDScreen::hideStage2b(){
    // Hide these elemnents
    QStringList stage2aElements = {
        "_2b_pbutton",
        "_2b_adult_patient",
        "_2b_child_patient",
    };

    for (const QString &str : stage2aElements) {
        showElementId(str, false);
    }
}

bool QAEDScreen::showStage2bChildPatient(){
    if(stage != Stage::PADS){
        return false;
    }

    hideStage2a();

    QStringList stage2bElements = {
        "_0_time",
        "_2b_pbutton",
        "_2b_adult_patient",
        // "_2b_child_patient",
    };

    // Show stage 2b elements
    for (const QString &str : stage2bElements) {
        showElementId(str, true);
    }

    refresh();
    return true;
}

bool QAEDScreen::showStage2bToggleChildPatient(bool show){
    showStage2bChildPatient();
    showVerifyStage(Stage::PADS, "_2b_adult_patient", !show);  
    return showVerifyStage(Stage::PADS, "_2b_child_patient", show);  
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
bool QAEDScreen::showMsg3aAnalyzing(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", show);
}

bool QAEDScreen::showMsg3aDontTouch(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", show);
}

bool QAEDScreen::showMsg3aStandBack(bool show){
    if (show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
        showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", show);
}

void QAEDScreen::clearMsg3a(){
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_analyzing", false);  
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_dont_touch", false);  
    showVerifyStage(Stage::ANALYZE, "_3a_stand_msg_stand_back", false);  
}

void QAEDScreen::hideStage3a(){
    // Hide these elemnents
    QStringList stage3aElements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        // "_0_time", 
        "_3a_sleepy", 
        "_3a_stand_back", 
        "_3a_stand_msg_analyzing", 
        "_3a_stand_msg_dont_touch", 
        "_3a_stand_msg_stand_back", 
    };

    for (const QString &str : stage3aElements) {
        showElementId(str, false);
    }
}

/* ECG graph */
void QAEDScreen::stage3bECG(){

    hideStage3a();

    // Show these elemnents
    QStringList stage3bElements = {
        "_0_time", 
        "_3b_grid",
        "_3b_grid_edge",
        "_3b_bpm_label",
        "_3b_bpm",
        // "_3b_label_sinus",
        // "_3b_label_vfib",
        // "_3b_label_vtach",
        // "_3b_label_asystole",
        // "_3b_pulse_healthy1",
        // "_3b_pulse_healthy2",
        // "_3b_pulse_vt1",
        // "_3b_pulse_vt2",
        // "_3b_pulse_vt3",
        // "_3b_pulse_vf1",
        // "_3b_pulse_asystole1",
        // "_3b_pulse_asystole2",
    };

    for (const QString &str : stage3bElements) {
        showElementId(str, true);
    }
    refresh();
}

bool QAEDScreen::showLabel3bSinus(bool show){
    if(stage == Stage::ANALYZE){
        hideStage3a();
    }

    if (show){ // Disable the rest of the stage's labels
        showVerifyStage(Stage::ANALYZE, "_3b_label_vfib", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_vtach", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_asystole", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3b_label_sinus", show);
}

bool QAEDScreen::showLabel3bVF(bool show){
    if(stage == Stage::ANALYZE){
        hideStage3a();
    }

    if (show){ // Disable the rest of the stage's labels
        showVerifyStage(Stage::ANALYZE, "_3b_label_sinus", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_vtach", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_asystole", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3b_label_vfib", show);
}

bool QAEDScreen::showLabel3bVT(bool show){
    if(stage == Stage::ANALYZE){
        hideStage3a();
    }

    if (show){ // Disable the rest of the stage's labels
        showVerifyStage(Stage::ANALYZE, "_3b_label_sinus", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_vfib", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_asystole", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3b_label_vtach", show);
}

bool QAEDScreen::showLabel3bAsystole(bool show){
    if(stage == Stage::ANALYZE){
        hideStage3a();
    }

    if (show){ // Disable the rest of the stage's labels
        showVerifyStage(Stage::ANALYZE, "_3b_label_sinus", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_vfib", false);  
        showVerifyStage(Stage::ANALYZE, "_3b_label_vtach", false);  
    }
    return showVerifyStage(Stage::ANALYZE, "_3b_label_asystole", show);
}

void QAEDScreen::clearLabel3b(){
    showVerifyStage(Stage::ANALYZE, "_3b_label_sinus", false);  
    showVerifyStage(Stage::ANALYZE, "_3b_label_vfib", false);  
    showVerifyStage(Stage::ANALYZE, "_3b_label_vtach", false);  
    showVerifyStage(Stage::ANALYZE, "_3b_label_asystole", false);  
}

bool QAEDScreen::showRhythm(int rhythm){
    if(stage == Stage::ANALYZE){
        hideStage3a();
    } else {
        return false;
    }

    QStringList ecgRhythms = {
        "_3b_pulse_healthy1",
        "_3b_pulse_healthy2",
        "_3b_pulse_vt1",
        "_3b_pulse_vt2",
        "_3b_pulse_vt3",
        "_3b_pulse_vf1",
        "_3b_pulse_asystole1",
        "_3b_pulse_asystole2",
    };

    if(rhythm >= ecgRhythms.length() || rhythm < 0){
        qInfo() << "QAEDScreen Error: No such rhythm, index oob. (Max =" << ecgRhythms.length()-1 ;
        return false;
    }

    showElementId("clippath", true); // Show clip mask

    for (int i = 0; i < ecgRhythms.length(); i++){
        showElementId(ecgRhythms[i], i==rhythm);
    }
        
    refresh();
}

void QAEDScreen::setBpm(int bpm){
    changeText(bpmText, QString("%1").arg(bpm, 2, 10, QChar('0')));
}

bool QAEDScreen::sweepEcg(int rIndex, int percent){
    if(percent < 0 || percent > 100){
        percent = 0;
    }


    // @@ Optimize
    QStringList ecgRhythms = {
        "_3b_pulse_healthy1",
        "_3b_pulse_healthy2",
        "_3b_pulse_vt1",
        "_3b_pulse_vt2",
        "_3b_pulse_vt3",
        "_3b_pulse_vf1",
        "_3b_pulse_asystole1",
        "_3b_pulse_asystole2",
    };

    int width = -1* (static_cast<double>(percent) / 100.0) * CLIPPATH_WIDTH;

    shiftElement(getElement(ecgRhythms[rIndex]), width, 0);
    refresh();
    return true;
}


/* STAGE 4 (Shock) Functions */

// Switch to the Stage 4 screen
void QAEDScreen::stage4(){

    QStringList stage4Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time",
        "_4a_bolt",
        "_4a_progress_bar_bg",
        // "_4a_countdown3",
        // "_4a_countdown2",
        // "_4a_countdown1",
        // "_4a_countdown0",
        // "_4a_progress_bar_9",
        // "_4a_progress_bar_8",
        // "_4a_progress_bar_7",
        // "_4a_progress_bar_6",
        // "_4a_progress_bar_5",
        // "_4a_progress_bar_4",
        // "_4a_progress_bar_3",
        // "_4a_progress_bar_2",
        // "_4a_progress_bar_1",
        // "_4a_progress_bar_0",
        // "_4a_msg_delivering_shock_dont_touch",
        // "_4a_msg_delivering_shock",
        // "_4a_msg_delivering_shock_delivered",
    };

    for (const QString &str : stage4Elements) {
        showElementId(str, true);
    }
    refresh();
}

bool QAEDScreen::shockProgress(int level){
    // level 0: clears the entry, defeault position
    // level 10: max, initiates shock

    if(level == 0){
        clearMsg4(); // Reset
    } else if (level == 1){
        showMsg4Shock(true);
    } else if (level == 10){
        showMsg4ShockDelivered(true);
    }

    QStringList shockCountdown = {
        "_4a_progress_bar_9",
        "_4a_progress_bar_8",
        "_4a_progress_bar_7",
        "_4a_progress_bar_6",
        "_4a_progress_bar_5",
        "_4a_progress_bar_4",
        "_4a_progress_bar_3",
        "_4a_progress_bar_2",
        "_4a_progress_bar_1",
        "_4a_progress_bar_0",
    };

    for (int i = 1; i <= shockCountdown.length(); i++) {
        showElementId(shockCountdown[i-1], i <= level);
 
        if(i == 1){
            showElementId("_4a_countdown3", i <= level);
        }
        if (i == 4) {
            showElementId("_4a_countdown2", i <= level);
        }
        if (i == 7) {
            showElementId("_4a_countdown1", i <= level);
        }
        if (i == 10) {
            showElementId("_4a_countdown0", i <= level);
        }
    }

    refresh();

    return true;
}

bool QAEDScreen::showMsg4Shock(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_dont_touch", false);
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_delivered", false);
    }
    return showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock", show);
}


bool QAEDScreen::showMsg4ShockDelivered(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_dont_touch", false);
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock", false);
    }
    return showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_delivered", show);
}

bool QAEDScreen::showMsg4DontTouch(bool show){
    if(show){ // Disable the rest of the stage's messages
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_delivered", false);
        showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock", false);
    }

    if(show){
        shockProgress(0); // Reset shock state
    }

    return showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_dont_touch", show);
}

void QAEDScreen::clearMsg4(){ // Hide all Stage 5 messages
    showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_dont_touch", false);
    showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock", false);
    showVerifyStage(Stage::SHOCK, "_4a_msg_delivering_shock_delivered", false);
}

/* STAGE 5 (CPR) Functions */

// Switch to the Stage 5 screen
void QAEDScreen::stage5(){

    QStringList stage5Elements = {
        "_0_shocks_label", 
        "_0_shocks_number", 
        "_0_time", 
        "_5_sleepy", 
        "_5a_cpr", 
        "_5a_cpr_indicator",
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

// Show various messages for stage 5 (CPR screen)
bool QAEDScreen::showStage5CPRIndicator(bool show){
    return showVerifyStage(Stage::CPR, "_5a_cpr_indicator", show);
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
    changeText(timeText, formattedTime);

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
        changeText(countdownText, countdownFormatted);
    }
}

void QAEDScreen::addShock(){
    changeText(shocksText, QString("%1").arg(shockCount++, 2, 10, QChar('0')));
}