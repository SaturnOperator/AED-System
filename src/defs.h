#ifndef DEFS_H
#define DEFS_H

#include <QDebug>
#include <QMetaType>

#include "aed_stages.h"

#define ICON_SIZE 35

#define POWER_CAPACITY 100 // Set battery level at 100%
#define SHOCK_POWER_DRAIN 5 // How much energy each shock consumes
#define LOW_BAT_THRESHOLD 10 // Show low battery error at 20% 

// #define CPR_COUNTDOWN_DURATION 120 // 2 minutes of CPR
#define CPR_COUNTDOWN_DURATION 20 // @@ change from 20s to
#define POWER_ON_DURRATION 15
#define CLIPPATH_WIDTH 860

enum class Rhythms{
    NONE,
    SINUS,
    ASYSTOLE,
    VFIB,
    VTACH,
};

Q_DECLARE_METATYPE(Rhythms)

#endif