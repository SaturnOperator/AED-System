#ifndef QSVGWIDGET_H
#define QSVGWIDGET_H

#include <QWidget>
#include <QSvgRenderer>
#include <QDomDocument>
#include <QMap>

class QSvgWidget : public QWidget {
    Q_OBJECT

public:
    explicit QSvgWidget(const QString &fileName, QWidget *parent = nullptr);
    ~QSvgWidget();

    // Show/hide layer in the SVG
    void showElement(QDomElement* element, bool show);
    void showElementId(const QString &id, bool show);

    void refresh(); // Updates SVG after making changes

protected:
    void paintEvent(QPaintEvent *event) override;
    QMap<QString, QDomElement*> elements; // Contains all the different layers with their id as the key

private:
    QSvgRenderer* svgRenderer;
    QDomDocument svgDom;
};

#endif // QSVGWIDGET_H