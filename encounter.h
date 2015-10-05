#ifndef ENCOUNTER_H
#define ENCOUNTER_H
#include <QByteArray>

class Encounter
{
private:
    quint8 _scn; //scenery
    quint8 _flags;
    quint8 _mainCam; //Main Camera
    quint8 _secCam;
    quint8 _visibleEn;      //NOT visible enemies
    quint8 _loadedEn;       //NOT loaded enemies
    quint8 _targetableEn;   //NOT targetable enemies
    quint8 _enabledEn;      //enabled enemies
    qint16 _coords[8][3];	//8 posible enemies' coordinate
    quint8 _enemyID[8];     //who is the enemy?
    quint16 _sect11[8];
    quint16 _sect12[8];
    quint16 _sect13[8];
    quint8 _sect14[8];
    quint8 _level[8];	//level in terms of low/med/high
public:
    Encounter(quint8 * data);
    inline void setScene(quint8 newscn){
        _scn = newscn;
    }
    inline quint8 getScene(){
        return _scn;
    }
    inline void setFlags(quint8 u2){
        _flags = u2;
    }
    inline quint8 getFlags(){
        return _flags;
    }

    void setFlags(quint8 mask, bool en);

    inline quint8 getMainCamNumber(){
        return _mainCam >> 4;
    }
    inline void setMainCamNumber(quint8 n){
        _mainCam &= 0xF;
        _mainCam |= (n<<4);
    }
    inline quint8 getMainCamAnimation(){
        return _mainCam & 0xF;
    }
    inline void setMainCamAnimation(quint8 n){
        _mainCam &= 0xF0;
        _mainCam |= (n & 0xF);
    }
    inline quint8 getSecCamNumber(){
        return _secCam >> 4;
    }
    inline void setSecCamNumber(quint8 n){
        _secCam &= 0xF;
        _secCam |= (n<<4);
    }
    inline quint8 getSecCamAnimation(){
        return _secCam & 0xF;
    }
    inline void setSecCamAnimation(quint8 n){
        _secCam &= 0xF0;
        _secCam |= (n & 0xF);
    }
    inline quint8 getEnabledEn(){
        return _enabledEn;
    }
    inline void setEnabledEn(quint8 en){
        _enabledEn = en;
    }
    inline bool getEnabledEn(quint8 mask){
        return _enabledEn & mask;
    }
    inline quint8 getVisibleEn(){
        return _visibleEn;
    }
    inline void setVisibleEn(quint8 en){
        _visibleEn = en;
    }
    inline bool getVisibleEn(quint8 mask){
        return _visibleEn & mask;
    }
    inline quint8 getTargetableEn(){
        return _targetableEn;
    }
    inline void setTargetableEn(quint8 en){
        _targetableEn = en;
    }
    inline bool getTargetableEn(quint8 mask){
        return _targetableEn & mask;
    }
    inline quint8 getLoadedEn(){
        return _loadedEn;
    }
    inline void setLoadedEn(quint8 en){
        _loadedEn = en;
    }
    inline bool getLoadedEn(quint8 mask){
        return _loadedEn & mask;
    }

    inline qint16 getCoordX(int enm){
        return _coords[enm][0];
    }

    inline qint16 getCoordY(int enm){
        return _coords[enm][1];
    }
    inline qint16 getCoordZ(int enm){
        return _coords[enm][2];
    }
    void setCoordX(quint8 enm, int coord);
    void setCoordY(quint8 enm, int coord);
    void setCoordZ(quint8 enm, int coord);
    quint8 getEnemyID(quint8 enm);
    void setEnemyID(quint8 enem, quint8 id);
    quint16 getsect11(quint8 enm);
    void setsect11(quint8 enm, quint16 s);
    quint16 getsect12(quint8 enm);
    void setsect12(quint8 enm, quint16 s);
    quint16 getsect13(quint8 enm);
    void setsect13(quint8 enm, quint16 s);
    quint8 getsect14(quint8 enm);
    void setsect14(quint8 enm, quint8 s);
    inline quint8 getLevel(int enm){
        return _level[enm];
    }

    inline void setLevel(int enm, quint8 lv){
        _level[enm] = lv;
    }
};

#endif // ENCOUNTER_H
