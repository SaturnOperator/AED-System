#ifndef AED_STAGES_H
#define AED_STAGES_H

#include <QString>

enum class Stage{
    NONE,
    POWER,
    PADS,
    ANALYZE,
    SHOCK,
    CPR,
    POST_USE
};

enum class Stage1Power {
    INIT,
    SAFETY_CHECK_OK,
    STAY_CALM,
    CHECK_RESPONSIVE,
    CALL_FOR_HELP,
    OPEN_AIRWAY,
    CHECK_BREATHING,
    DONE,
    ERROR_SYSTEM_FAULT, // Safety check fails
    ERROR_NO_PADS,  // No pads attached
    ERROR_LOW_BATTERY, // Replace battery

};

enum class Stage2Install {
    INIT,
    ADULT_PATIENT,
    CHILD_PATIENT,
    REMOVE_PADS,
    EXPOSE_CHEST,
    ATTACH_PADS,
    CHECK_PAD_CONNECTION,
    DONE,
    ERROR_ADJUST_PADS,
    ERROR_CONNECT_PADS,
};

enum class Stage3Analyze {
    INIT,
    ANALYZING, // Wait, don't touch
    VTACH_DETECTED, // Shockable rhythms, continue to stage 4 (shock)
    VFIB_DETECTED, // Shockable rhythms, continue to stage 4 (shock)
    DONE,
    ERROR_NO_RHYTHM, // Skip shock, continue to stage 5 (cpr)
    ERROR_ASYSTOLE, // Flatline, skip shock, continue to stage 5 (cpr)
    ERROR_SINUS_RHYTHM, // End system, AED completed successfully 
    ERROR_DONT_TOUCH,
};

enum class Stage4Shock {
    INIT,
    CHECK_PAD_CONNECTION,
    COUNTDOWN, // Wait, don't touch
    SHOCK,
    DONE,
    ERROR_NO_SHOCK_ADVISED, // Continue to stage 4
    ERROR_DONT_TOUCH,
    ERROR_CONNECT_PADS,
};

enum class Stage5CPR {
    INIT,
    START_CPR,
    STOP_CPR,
    DONE, // Go back to stage 3 (analyze)
};

enum class Stage6PostUse {
    INIT,
    POWER_OFF,
    MAINTENANCE_CHECK,
    DONE,
    ERROR_MAINTENANCE_REQUIRED,
};

// Inline function to convert a Stage enum value to a string
inline QString stageToString(Stage stage) {
    switch (stage) {
        case Stage::NONE:
            return "No stage selected";
        case Stage::POWER:
            return "Power On";
        case Stage::PADS:
            return "Install Pads";
        case Stage::ANALYZE:
            return "Analyzing";
        case Stage::SHOCK:
            return "Shock";
        case Stage::CPR:
            return "CPR";
        case Stage::POST_USE:
            return "Post Use";
        default:
            return "Unknown";
    }
}

#endif // AED_STAGES_H
