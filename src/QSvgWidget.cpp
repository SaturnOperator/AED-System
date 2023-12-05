#include "QSvgWidget.h"
#include <QPainter>
#include <QFile>
#include <QPainterPath>

QSvgWidget::QSvgWidget(const QString &fileName, QWidget *parent)
    : QWidget(parent), svgRenderer(new QSvgRenderer(this)) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        svgDom.setContent(&file);
        file.close();
        svgRenderer->load(svgDom.toByteArray());
        this->setFixedSize(svgRenderer->defaultSize());

        // Find all elements (layers) in the SVG
        // Put them into elements Map where the id is the key and the element is value
        QDomElement elem = svgDom.documentElement().firstChildElement();
        while (!elem.isNull()) {
            if (elem.hasAttribute("id")) {
                QDomElement* newElem = new QDomElement(elem);
                elements.insert(elem.attribute("id"), newElem);
            }
            elem = elem.nextSiblingElement();
        }
    }
}

QSvgWidget::~QSvgWidget() {
}

void QSvgWidget::showElement(QDomElement* element, bool show){
    // Changes will not show until you call refresh() after using this method
    if (element) {
        element->setAttribute("style", show ? "" : "display:none");
    }
};

void QSvgWidget::showElementId(const QString &id, bool show) {
    if (elements.contains(id)) {
        QDomElement *elem = elements.value(id);
        if (elem) {
            showElement(elem, show);
        }
    }
}

QDomElement* QSvgWidget::getElement(const QString &id) {
    if (elements.contains(id)) {
        return elements.value(id);
    }
    return nullptr;
}

// Changes text value of an element
void QSvgWidget::changeText(QDomElement* element, const QString &s){
    if(element){
        element->firstChild().firstChild().firstChild().firstChild().setNodeValue(s);
        refresh();
    }
}

void QSvgWidget::refresh(){
    svgRenderer->load(svgDom.toByteArray());
    QSvgWidget::update();
}

// This method is called everytime the svg is updated
void QSvgWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Add a border radius to the overall svg renderer
    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10); // Add 10px rounded edge
    painter.setClipPath(path); // Set the clip path to the painter

    svgRenderer->render(&painter);
}