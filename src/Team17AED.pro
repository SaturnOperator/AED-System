TEMPLATE = app
TARGET = Team17AED
QT += widgets svg xml

FONT_PATH = assets/fonts
HEADERS += QCustomIconsFont.h

SOURCES += main.cpp AEDController.cpp
HEADERS += defs.h aed_stages.h AEDController.h

SOURCES += QIconButton.cpp QSvgWidget.cpp QAEDScreen.cpp QScreenSettings.cpp
HEADERS += QIconButton.h QSvgWidget.h QAEDScreen.h QScreenSettings.h
