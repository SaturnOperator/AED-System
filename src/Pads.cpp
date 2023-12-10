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

    if(depth == 0){
        clear = true;
        qInfo() << "clear";
    } else {
        clear = false;
    }
}

void Pads::setAdult(bool a){
    adult = a;
}

void Pads::setRhythm(Rhythms r){
    rhythm = r;
}

void Pads::setAttached(bool b){
    attached = b;
}

void Pads::setConnected(bool b){
    connected = b;
}

int Pads::getBpm(){
    return bpm;
}

int Pads::getDepth(){
    return depth;
}

bool Pads::isAttached(){
    return attached;
}

bool Pads::isConnected(){
    return connected;
}

bool Pads::getAdult(){
    return adult;
}

Rhythms Pads::getRhythm(){
    return rhythm;
}

bool Pads::isClear(){
    return clear;
}