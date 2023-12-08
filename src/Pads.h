#ifndef PADS_H
#define PADS_H

#include <QObject>

#include "defs.h"

class Pads : public QObject {
    Q_OBJECT

public:
    explicit Pads(QObject *parent = nullptr);

    void attach();
    void detach();
    void shock();

    void setBpm(int b);
    void setDepth(int d);
    void setAdult(bool adult);
    void setRhythm(Rhythms r);

    int getBpm();
    int getDepth();
    bool getAdult();
    Rhythms getRhythm();

signals:
    void depthChanged(int newDepth);

private:
	bool attached;
    bool adult;
    int depth; // Compression level
    int bpm; // Heart rate
    Rhythms rhythm;
};

#endif // PADS_H