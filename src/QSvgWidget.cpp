#include "QSvgWidget.h"
#include <QPainter>
#include <QFile>

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

void QSvgWidget::refresh(){
    svgRenderer->load(svgDom.toByteArray());
    QSvgWidget::update();
}

void QSvgWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    svgRenderer->render(&painter);
}