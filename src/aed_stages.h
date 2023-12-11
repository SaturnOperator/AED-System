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
    IDLE = -1, // Stage not active yet
    DONE = 0,
    INIT = 1, // Start stage
    SAFETY_CHECK_OK = 2,
    STAY_CALM = 3,
    CHECK_RESPONSIVE = 4,
    CALL_FOR_HELP = 5,
    OPEN_AIRWAY = 6,
    CHECK_BREATHING = 7,
    ERROR_SYSTEM_FAULT = -2, // Safety check fails
    ERROR_NO_PADS = -3,  // No pads attached
    ERROR_LOW_BATTERY = -4, // Replace battery
};

enum class Stage2Install {
    IDLE = -1, // Stage not active yet
    DONE = 0,
    INIT = 1, // Start stage
    ADULT_PATIENT = 2,
    CHILD_PATIENT = 3,
    REMOVE_PADS = 4,
    EXPOSE_CHEST = 5,
    ATTACH_PADS = 6,
    CHECK_PAD_CONNECTION = 7,
    ERROR_ATTACH_PADS = -2,
    ERROR_CONNECT_PADS = -3,
};

enum class Stage3Analyze {
    IDLE = -1, // Stage not active yet
    DONE = 0,
    INIT = 1, // Start stage
    ANALYZING = 2, // Wait, don't touch
    VTACH_DETECTED = 3, // Shockable rhythms, continue to stage 4 (shock)
    VFIB_DETECTED = 4, // Shockable rhythms, continue to stage 4 (shock)
    ERROR_NO_RHYTHM = 5, // Skip shock, continue to stage 5 (cpr)
    ERROR_ASYSTOLE = 6, // Flatline, skip shock, continue to stage 5 (cpr)
    ERROR_SINUS_RHYTHM = 7, // End system, AED completed successfully 
    ERROR_DONT_TOUCH = 8,
};

enum class Stage4Shock {
    IDLE = -1, // Stage not active yet
    DONE = 0,
    INIT = 1, // Start stage
    CHECK_PAD_CONNECTION = 2,
    COUNTDOWN = 3, // Wait, don't touch
    SHOCK = 4,
    ERROR_NO_SHOCK_ADVISED = -2, // Continue to stage 4
    ERROR_DONT_TOUCH = -3,
    ERROR_CONNECT_PADS = -4,
};

enum class Stage5CPR {
    IDLE = -1, // Stage not active yet
    DONE = 0, // Go back to stage 3 (analyze)
    INIT = 1, // Start stage
    START_CPR = 2,
    STOP_CPR = 3,
};

enum class Stage6PostUse {
    IDLE = -1, // Stage not active yet
    DONE = 0,
    INIT = 1, // Start stage
    POWER_OFF = 2,
    MAINTENANCE_CHECK = 3,
    ERROR_MAINTENANCE_REQUIRED = -2,
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
