/*********************************************************
 * encounter.cpp
 *
 * Encapsulates a whole line from the scene.out file.
 * Every attribute of the class corresponds to a section
 * in the line.
 *
 **********************************************************/

#include <cstring>
#include "encounter.h"

Encounter::Encounter(quint8 * data){
    _scn = data[0];
    _flags = data[1];
    _mainCam = data[2];
    _secCam = data[3];
    _visibleEn = data[4];
    _loadedEn = data[5];
    _targetableEn = data[6];
    _enabledEn = data[7];
    memcpy(_coords, &data[8], 48); //copy 48 bytes from data array 9th pos to _coords pointer
    memcpy(_enemyID, &data[56], 8);  //1 byte for _enemy
    memcpy(_sect11, &data[64], 16);
    memcpy(_sect12, &data[80], 16);
    memcpy(_sect13, &data[96], 16);
    memcpy(_sect14, &data[112], 8);
    memcpy(_level, &data[120], 8);
}

void Encounter::setFlags(quint8 mask, bool en){
    _flags &= mask;
    if(en){
        _flags |= ~mask;
    }
}

quint8 Encounter::getEnemyID(quint8 enm){
    return _enemyID[enm] - 0x10;
}

void Encounter::setEnemyID(quint8 enem, quint8 id){
    _enemyID[enem] = id + 0x10;
}

void Encounter::setCoordX(quint8 enm, int coord){
    _coords[enm][0] = coord;
}

void Encounter::setCoordY(quint8 enm, int coord){
    _coords[enm][1] = coord;
}

void Encounter::setCoordZ(quint8 enm, int coord){
    _coords[enm][2] = coord;
}

quint16 Encounter::getsect11(quint8 enm){
    return _sect11[enm];
}

quint16 Encounter::getsect12(quint8 enm){
    return _sect12[enm];
}

quint16 Encounter::getsect13(quint8 enm){
    return _sect13[enm];
}

quint8 Encounter::getsect14(quint8 enm){
    return _sect14[enm];
}

void Encounter::setsect11(quint8 enm, quint16 s){
    _sect11[enm] = s;
}

void Encounter::setsect12(quint8 enm, quint16 s){
    _sect12[enm] = s;
}

void Encounter::setsect13(quint8 enm, quint16 s){
    _sect13[enm] = s;
}

void Encounter::setsect14(quint8 enm, quint8 s){
    _sect14[enm] = s;
}
