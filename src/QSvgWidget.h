#ifndef QSVGWIDGET_H
#define QSVGWIDGET_H

#include <QWidget>
#include <QSvgRenderer>
#include <QDomDocument>

class QSvgWidget : public QWidget {
    Q_OBJECT

public:
    explicit QSvgWidget(const QString &fileName, QWidget *parent = nullptr);
    ~QSvgWidget();

    void showElement(const QString &id, bool show);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QSvgRenderer *svgRenderer;
    QDomDocument svgDom;
};

#endif // QSVGWIDGET_H