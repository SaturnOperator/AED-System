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

        // Set the widget size to match the SVG's default size
        this->setFixedSize(svgRenderer->defaultSize());
    }
}

QSvgWidget::~QSvgWidget() {
    // svgRenderer is a child of this widget, so it will be deleted automatically
}

void QSvgWidget::showElement(const QString &id, bool show) {
    QDomElement elem = svgDom.documentElement().firstChildElement();
    while (!elem.isNull()) {
        // Check for <a> elements inside the current element
        QDomNodeList elements = elem.elementsByTagName("a");
        for (int i = 0; i < elements.count(); ++i) {
            QDomElement element = elements.at(i).toElement();
            qInfo() << element.attribute("xlink:href");
            if (element.attribute("xlink:href") == id) {
                element.setAttribute("style", show ? "" : "display:none");
                svgRenderer->load(svgDom.toByteArray());
                update();
                return; // Exit the function once the target is found and updated
            }
        }

        // Check if the current element itself has the matching ID
        if (elem.attribute("id") == id) {
            elem.setAttribute("style", show ? "" : "display:none");
            svgRenderer->load(svgDom.toByteArray());
            update();
            return; // Exit the function once the target is found and updated
        }
        elem = elem.nextSiblingElement();
    }
}

void QSvgWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    svgRenderer->render(&painter);
}
