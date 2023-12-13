#include "QIconButton.h"

QIconButton::QIconButton(const QString &text, bool altDesign, QWidget *parent)
    : alt(altDesign), QPushButton(text, parent) {

    size = ICON_SIZE;

    QCustomIconsFont& iconsFont = QCustomIconsFont::instance();

    setFont(iconsFont);

    setSize(size);
}

void QIconButton::on(){
    setEnabled(false);
}

void QIconButton::off(){
    setEnabled(true);
}

void QIconButton::setSize(int diameter){
    if (diameter % 2 != 0) {
        diameter++; // Make number even
    }

    size = diameter;

    setFixedSize(diameter, diameter);
    stylize();
}

void QIconButton::stylize(){
    if(!alt){
        setStyleSheet( 
            QString(
                "QPushButton { "
                "    color: #a2a3a4; "
                "    background-color: #223145; "
                "    border-radius: %1px; "
                "    font-size: %2px;"
                "}"
                "QPushButton:hover { "
                "    background-color: #0f1a23; "
                "}"
                "QPushButton:pressed { "
                "    background-color: #0b1319; "
                "}"
            ).arg(size/2).arg(size/2.5)
        );
    } else {
        setStyleSheet( 
            QString(
                "QPushButton { "
                "    color: #a2a3a4; "
                "    background-color: #1c2329; "
                "    border-radius: %1px; "
                "    font-size: %2px;"
                "}"
                "QPushButton:disabled { "
                "    background-color: #de4c33; "
                "}"
                "QPushButton:hover { "
                "    background-color: #0b1319; "
                "}"
                "QPushButton:pressed { "
                "    background-color: #442c3b; "
                "}"
            ).arg(size/2).arg(size/2.5)
        );
    }
}