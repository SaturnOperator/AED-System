#ifndef QCUSTOMICONSFONT_H
#define QCUSTOMICONSFONT_H

#include <QFont>

class QCustomIconsFont : public QFont {
public:
    static QCustomIconsFont& instance() {
        static QCustomIconsFont font; // Singleton instance
        return font;
    }

private:
    QCustomIconsFont() {
        setFamily("Font Awesome 6 Free"); // Icons font
        setPointSize(14); // Icon size
    }

    // Disable copy constructor and assignment operator
    QCustomIconsFont(const QCustomIconsFont&) = delete;
    QCustomIconsFont& operator=(const QCustomIconsFont&) = delete;
};

#endif // QCUSTOMICONSFONT_H
