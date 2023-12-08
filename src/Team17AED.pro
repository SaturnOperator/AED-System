TEMPLATE = app
TARGET = Team17AED
QT += widgets svg xml

# Fast compiling option
CONFIG += fast

# Include fonts
FONT_PATH = assets/fonts
HEADERS += QCustomIconsFont.h

# Main system classes
SOURCES += main.cpp AEDController.cpp StageManager.cpp Pads.cpp
HEADERS += defs.h aed_stages.h AEDController.h StageManager.h Pads.h

# Stage classes for AED System
SOURCES += Stage1.cpp Stage2.cpp Stage3.cpp Stage4.cpp Stage5.cpp Stage6.cpp
HEADERS += Stage1.h Stage2.h Stage3.h Stage4.h Stage5.h Stage6.h

# Custom widget classes
SOURCES += QIconButton.cpp QSvgWidget.cpp QAEDScreen.cpp QScreenSettings.cpp
HEADERS += QIconButton.h QSvgWidget.h QAEDScreen.h QScreenSettings.h
