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
    bool isAttached();
    bool isConnected();
    bool getAdult();
    Rhythms getRhythm();
    bool isClear(); // Check if user needs to maintain distance

signals:
    void depthChanged(int newDepth);

private:
	bool attached;	// Pads attached to patient
	bool connected; // Pads connected to AED
    bool adult;
    int depth; // Compression level
    int bpm; // Heart rate
    Rhythms rhythm;

    bool clear; // If true, user needs to step back for shock and ECG
};

#endif // PADS_H