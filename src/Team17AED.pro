TEMPLATE = app
TARGET = Team17AED
QT += widgets svg xml

FONT_PATH = assets/fonts
HEADERS += QCustomIconsFont.h

SOURCES += main.cpp
HEADERS += defs.h

SOURCES += QIconButton.cpp QSvgWidget.cpp QAEDScreen.cpp
HEADERS += QIconButton.h QSvgWidget.h QAEDScreen.h
