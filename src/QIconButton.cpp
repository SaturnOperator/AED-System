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
            "    color: white; "
            "    background-color: #111111; "
            "    border-radius: %1px; "
            "    font-size: %1px;"
            "}"
            "QPushButton:hover { "
            "    background-color: #202020; "
            "}"
            "QPushButton:pressed { "
            "    background-color: #093eb8; "
            "}"
            "QPushButton:disabled { "
            "    background-color: #545454; "
            "    border: 2px solid #545454"
            "}"
        ).arg(size/2, size/2)
    );
}