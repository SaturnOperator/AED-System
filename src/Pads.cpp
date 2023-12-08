#include "Pads.h"

Pads::Pads(QObject *parent)
    : QObject(parent), attached(false), adult(true), depth(0), bpm(0), rhythm(Rhythms::NONE){
    
}

void Pads::attach(){
    attached = true;
}

void Pads::detach(){
    attached = false;
}

void Pads::shock(){
    qInfo() << "Patient shocked";
}

void Pads::setBpm(int b){
    bpm = b;
}

void Pads::setDepth(int d){
    if (depth != d) {
        depth = d;
        emit depthChanged(d); // Emit the signal when depth changes
    }
}

void Pads::setAdult(bool a){
    adult = a;
}

void Pads::setRhythm(Rhythms r){
    rhythm = r;   
}

int Pads::getBpm(){
    return bpm;
}

int Pads::getDepth(){
    return depth;
}

bool Pads::getAdult(){
    return adult;
}

Rhythms Pads::getRhythm(){
    return rhythm;
}