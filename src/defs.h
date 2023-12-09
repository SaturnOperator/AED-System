#ifndef DEFS_H
#define DEFS_H

#include <QDebug>
#include <QMetaType>

#include "aed_stages.h"

#define ICON_SIZE 50

// #define CPR_COUNTDOWN_DURATION 120 // 2 minutes of CPR
#define CPR_COUNTDOWN_DURATION 20 // @@ change from 20s to

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