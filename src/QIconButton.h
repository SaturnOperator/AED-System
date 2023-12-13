#ifndef QICONBUTTON_H
#define QICONBUTTON_H

#include "defs.h"

#include <QPushButton>

#include "QCustomIconsFont.h"

class QIconButton : public QPushButton {
    Q_OBJECT

    public:
        explicit QIconButton(const QString &text, bool altDesign = false, QWidget *parent = nullptr);
        void on();
        void off();
        void setSize(int size);

    private:
        void stylize();
        int size;
        bool alt;
};

#endif // QICONBUTTON_H
