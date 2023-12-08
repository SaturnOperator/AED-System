#include "QSvgWidget.h"
#include <QPainter>
#include <QFile>
#include <QPainterPath>

QSvgWidget::QSvgWidget(const QString &fileName, QWidget *parent)
    : QWidget(parent), svgRenderer(new QSvgRenderer(this)) {
    mutex = new QMutex;
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
                // qInfo() << elem.attribute("id");
                QDomElement* newElem = new QDomElement(elem);
                elements.insert(elem.attribute("id"), newElem);
            }
            elem = elem.nextSiblingElement();
        }

        // Search svg defs for clippaths 
        elem = svgDom.documentElement().firstChildElement("defs").firstChildElement("clipPath");
        // while (!elem.isNull()) {
        //     if (elem.hasAttribute("id")) {
        //         QDomElement* newElem = new QDomElement(elem);
        //         elements.insert(elem.attribute("id"), newElem);
        //     }
        //     elem = elem.nextSiblingElement();
        // }
    }
}

QSvgWidget::~QSvgWidget() {
    delete mutex;
}

void QSvgWidget::showElement(QDomElement* element, bool show){
    // Changes will not show until you call refresh() after using this method
    QMutexLocker locker(mutex);
    if (element) {
        element->setAttribute("style", show ? "" : "display:none");
    }
};

void QSvgWidget::shiftElement(QDomElement* element, int x, int y){
    // Changes will not show until you call refresh() after using this method
    QMutexLocker locker(mutex);
    if (element) {
        QString val = "translate(%1,%2)";
        element->setAttribute("transform", val.arg(x).arg(y));
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

        // Search for tspan
        // while (!element->isNull()) {
        //     if (element->tagName() == "tspan") {
        //         element->firstChild().setNodeValue(s);
        //         break; 
        //     }
        //     // Move to the next child element (if it exists)
        //     element = new QDomElement(element->firstChildElement());
        // }
    }
}

void QSvgWidget::resizeMask(QDomElement* element, float width, float height){
    if(element){
        if(width >= 0){
            element->firstChildElement("rect").setAttribute("width", width);
        }
        if(height >= 0){
            element->firstChildElement("rect").setAttribute("height", height);
        }
        refresh();
    }
}

void QSvgWidget::refresh(){
    QMutexLocker locker(mutex);
    svgRenderer->load(svgDom.toByteArray());
    QSvgWidget::update();
}

// This method is called everytime the svg is updated
void QSvgWidget::paintEvent(QPaintEvent *event) {
    QMutexLocker locker(mutex);
    QPainter painter(this);

    // Add a border radius to the overall svg renderer
    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10); // Add 10px rounded edge
    painter.setClipPath(path); // Set the clip path to the painter

    svgRenderer->render(&painter);
}