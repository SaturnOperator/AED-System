#include "QIconButton.h"

QIconButton::QIconButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent) {

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
}