#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <encounter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();

    void on_actionOpen_triggered();

    void on_loadEncounter_clicked();

    void on_enemySlotBox_currentIndexChanged(int index);

    void on_sceneBox_currentIndexChanged(int index);

    void on_noEscape_stateChanged(int arg1);

    void on_noVictory_stateChanged(int arg1);

    void on_showTimer_stateChanged(int arg1);

    void on_noExpGain_stateChanged(int arg1);

    void on_noExpScreen_stateChanged(int arg1);

    void on_surpriseAttack_stateChanged(int arg1);

    void on_backAttack_stateChanged(int arg1);

    void on_scriptedBattle_stateChanged(int arg1);

    void on_mainCamNumberBox_valueChanged(int arg1);

    void on_mainCamAnimBox_valueChanged(int arg1);

    void on_secCamNumberBox_valueChanged(int arg1);

    void on_secCamAnimBox_valueChanged(int arg1);

    void on_levelBox_valueChanged(int arg1);

    void on_enemyNameBox_currentIndexChanged(int index);

    void on_enabledCheck_stateChanged(int arg1);

    void on_visibleCheck_stateChanged(int arg1);

    void on_targetableCheck_stateChanged(int arg1);

    void on_loadedCheck_stateChanged(int arg1);

    void on_xCoordBox_valueChanged(int arg1);

    void on_yCoordBox_valueChanged(int arg1);

    void on_zCoordBox_valueChanged(int arg1);

    void on_sect11Box_valueChanged(int arg1);

    void on_sect12Box_valueChanged(int arg1);

    void on_sect13Box_valueChanged(int arg1);

    void on_sect14Box_valueChanged(int arg1);

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;
    std::vector<Encounter> _scene;
    Encounter * _currEncounter;
    quint8 _enemymask;
};

#endif // MAINWINDOW_H
