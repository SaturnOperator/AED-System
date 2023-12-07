#ifndef QSVGWIDGET_H
#define QSVGWIDGET_H

#include <QWidget>
#include <QSvgRenderer>
#include <QDomDocument>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>

class QSvgWidget : public QWidget {
    Q_OBJECT

public:
    explicit QSvgWidget(const QString &fileName, QWidget *parent = nullptr);
    ~QSvgWidget();


    QDomElement* getElement(const QString &id);

    void refresh(); // Updates SVG after making changes

protected:
    // Show/hide layer in the SVG
    void showElement(QDomElement* element, bool show);
    void showElementId(const QString &id, bool show);
    void changeText(QDomElement* element, const QString &s);
    void resizeMask(QDomElement* element, float width = -1, float height = -1);

    void paintEvent(QPaintEvent *event) override;
    QMap<QString, QDomElement*> elements; // Contains all the different layers with their id as the key
    QMutex* mutex; // Make showVerifyStage() multithread safe

private:
    QSvgRenderer* svgRenderer;
    QDomDocument svgDom;
};

#endif // QSVGWIDGET_H