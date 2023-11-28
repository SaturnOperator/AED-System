#include "QAEDScreen.h"

QAEDScreen::QAEDScreen(QWidget *parent)
    : QSvgWidget("./screen.svg", parent) {
    // Constructor implementation for QAEDScreen
    setStage(Stage::CPR); // Start in CPR stage

}

void QAEDScreen::setStage(Stage stage){
    qInfo() << elements.keys();
    for(QDomElement* e : elements){
        showElement(e, false);
    }
    showElementId("background", true);
    refresh();
}