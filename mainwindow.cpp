#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "names.h"
#include "parameters.h"
#include <QtWidgets>
#include <QScrollArea>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sceneBox->addItems(CreateStageList());
    ui->enemyNameBox->addItems(CreateEnemyList());
    ui->menuBar->addAction(tr("About..."), this, SLOT(about()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/***************************
 * File operation related  *
 ***************************/

void MainWindow::on_actionOpen_triggered()
{
    //Is a previous file opened?
    if(!_scene.empty()){
        _scene.clear();
        _currEncounter = NULL;
        ui->MiscBox->setEnabled(false);
        ui->enemyStuffBox->setEnabled(false);
    }
    QString selectedFilter;
    QString filename = QFileDialog::getOpenFileName(this,"Open scene.out file.","","FF8 Battle Scene Files (*.out)",&selectedFilter);
    if(!filename.isEmpty()){

        QFile f(filename);
        QDataStream in(&f);

        in.setVersion(QDataStream::Qt_5_5);

        if(!f.open(QIODevice::ReadOnly))
            qFatal("Couldn't open the file.");

        quint8 temp[128];
        unsigned k = 0;
        for(unsigned i = 0; i<1024; ++i){
            for(k = 0; k<128; ++k){
                in >> temp[k];
            }
            _scene.push_back(Encounter(temp));
        }
        f.close();
        ui->encounterGroupBox->setEnabled(true);
        ui->actionSave->setEnabled(true);
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,"Save scene.out file.","scene.out","FF8 Battle Scene Files (*.out)",&selectedFilter);

    QFile f(filename);
    QDataStream out(&f);

    out.setVersion(QDataStream::Qt_5_5);

    if(!f.open(QIODevice::WriteOnly))
        qFatal("Couln't create the file.");

    out.writeRawData((const char*)&(_scene[0]) ,131072);
    f.close();

}

/****************
 * About window *
 ****************/
void MainWindow::about()
{
    qreal scaleX = qApp->desktop()->logicalDpiX()/96;
    qreal scaleY = qApp->desktop()->logicalDpiY()/96;
    QDialog about(this, Qt::Dialog | Qt::CustomizeWindowHint);
    about.setMinimumSize(380*scaleX,220*scaleY);

    QFont font;
    font.setPointSize(12);
    font.setBold(true);

    QLabel image(&about);
    image.setPixmap(QPixmap(":/images/cactilio128.png"));

    QLabel name(PROG_FULLNAME, &about);
    QPalette pal = name.palette();
    pal.setColor(QPalette::WindowText, QColor(0,128,16));
    name.setPalette(pal);
    name.setFont(font);
    name.setMinimumWidth(about.width());
    name.setAlignment(Qt::AlignHCenter);

    font.setPointSize(8);
    font.setBold(false);

    QLabel aboutText(tr("<b>By JeMaCheHi</b><br/>"
                    "See Cactilio's forum thread at <a href=\"http://forums.qhimm.com/index.php?topic=16275.0\">qhimm forums</a><br/>"
                    "See also the scene.out <a href=\"http://forums.qhimm.com/index.php?topic=15816.0\">research thread</a><br/><br/>"


                    "<b>Thanks to:</b><br/>"
                    "sithlord48 for helping me with lots of advices for Qt<br/>"
                    "Shard(for writing an <a href=\"http://wiki.qhimm.com/view/FF8/Encounter_Codes\">encounter list</a>)<br/>"
                    "kaspar01(<a href=\"http://forums.qhimm.com/index.php?topic=15906.msg225667#msg225667\">stage names list</a> to start with)<br/>"
                    "MakiPL and Halfer(battle stages research)<br/>"
                    "myst6re(Deling src as sample to code this :D)<br/>"
                    "kyo-tux(for his <a href=\"http://kyo-tux.deviantart.com/art/GiNUX-126818033\">icon pack</a>)"
                    ), &about);
    aboutText.setTextInteractionFlags(Qt::LinksAccessibleByMouse | Qt::LinksAccessibleByKeyboard);
    aboutText.setTextFormat(Qt::RichText);
    aboutText.setOpenExternalLinks(true);
    aboutText.setFont(font);

    QLabel programmedWith(QString(tr("Programmed with Qt %1")).arg(QT_VERSION_STR), &about);
    programmedWith.setPalette(pal);
    programmedWith.setFont(font);

    QPushButton button(tr("Close"), &about);
    connect(&button, SIGNAL(released()), &about, SLOT(close()));

    QHBoxLayout * textLayout = new QHBoxLayout;
        textLayout->addWidget(&image,0,Qt::AlignCenter);
        textLayout->addWidget(&aboutText);
    QHBoxLayout * buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(&button,1,Qt::AlignLeft|Qt::AlignBottom);
        buttonLayout->addSpacing(3);
        buttonLayout->addWidget(&programmedWith,1,Qt::AlignRight|Qt::AlignBottom);
    QVBoxLayout * aboutLayout = new QVBoxLayout;
        aboutLayout->addWidget(&name);
        aboutLayout->addLayout(textLayout);
        aboutLayout->addLayout(buttonLayout);

    about.setLayout(aboutLayout);
    about.setMaximumSize(aboutLayout->maximumSize());
    about.exec();
}

void MainWindow::on_loadEncounter_clicked()
{
    _currEncounter = &(_scene[ui->encounterID->value()]);
    ui->MiscBox->setEnabled(true);

    //Scenario Combo Box data
    ui->sceneBox->setCurrentIndex(_currEncounter->getScene());

    //Battle status flags
    quint8 flags = _currEncounter->getFlags();
    ui->noEscape->setChecked(flags & 0x1);
    ui->noVictory->setChecked(flags & 0x2);
    ui->showTimer->setChecked(flags & 0x4);
    ui->noExpGain->setChecked(flags & 0x8);
    ui->noExpScreen->setChecked(flags &0x10);
    ui->surpriseAttack->setChecked(flags & 0x20);
    ui->backAttack->setChecked(flags & 0x40);
    ui->scriptedBattle->setChecked(flags & 0x80);

    //Camera data
    ui->mainCamNumberBox->setValue(_currEncounter->getMainCamNumber());
    ui->mainCamAnimBox->setValue(_currEncounter->getMainCamAnimation());
    ui->secCamNumberBox->setValue(_currEncounter->getSecCamNumber());
    ui->secCamAnimBox->setValue(_currEncounter->getSecCamAnimation());

    //Reset enemy slot editing
    ui->enemyStuffBox->setEnabled(true);
    ui->enemySlotBox->setCurrentIndex(-1);
}



/***************************
 * Scenario related data
 **************************/

//Battle stage changed
void MainWindow::on_sceneBox_currentIndexChanged(int index)
{
    if( ui->sceneBox->isEnabled() )
    _currEncounter->setScene((quint8)index);
}

void MainWindow::on_noEscape_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xFE;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_noVictory_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xFD;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_showTimer_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xFB;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_noExpGain_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xF7;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_noExpScreen_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xEF;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_surpriseAttack_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xDF;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_backAttack_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0xBF;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_scriptedBattle_stateChanged(int arg1)
{
    bool state;
    quint8 mask = 0x7F;
    arg1==0 ? state = false : state = true;
    _currEncounter->setFlags(mask,state);
}

void MainWindow::on_mainCamNumberBox_valueChanged(int arg1)
{
    _currEncounter->setMainCamNumber( (quint8)arg1 );
}

void MainWindow::on_mainCamAnimBox_valueChanged(int arg1)
{
    _currEncounter->setMainCamAnimation( (quint8)arg1 );

}

void MainWindow::on_secCamNumberBox_valueChanged(int arg1)
{
    _currEncounter->setSecCamNumber( (quint8)arg1 );
}


void MainWindow::on_secCamAnimBox_valueChanged(int arg1)
{
    _currEncounter->setSecCamAnimation( (quint8)arg1 );
}

/****************************
 * Enemy group box data
 ****************************/

//Enemy slot changed
void MainWindow::on_enemySlotBox_currentIndexChanged(int index)
{
    _enemymask = 0x80 >> index;

    ui->levelLabel->setEnabled(true);
    ui->levelBox->setEnabled(true);
    ui->nameLabel->setEnabled(true);
    ui->enemyNameBox->setEnabled(true);
    ui->enemyStatGroup->setEnabled(true);
    ui->coordsGroup->setEnabled(true);
    ui->unknownGroup->setEnabled(true);

    //Enemy name combo
    ui->enemyNameBox->setCurrentIndex( _currEncounter->getEnemyID(index) );
    ui->levelBox->setValue(_currEncounter->getLevel(index));

    //Enemy status checkboxes
    ui->enabledCheck->setChecked(_currEncounter->getEnabledEn(_enemymask));
    ui->visibleCheck->setChecked(_currEncounter->getVisibleEn(_enemymask));
    ui->targetableCheck->setChecked(_currEncounter->getTargetableEn(_enemymask));
    ui->loadedCheck->setChecked(_currEncounter->getLoadedEn(_enemymask));

    //Coordinates
    ui->xCoordBox->setValue(_currEncounter->getCoordX(index));
    ui->yCoordBox->setValue(_currEncounter->getCoordY(index));
    ui->zCoordBox->setValue(_currEncounter->getCoordZ(index));

    //Unknowns
    ui->sect11Box->setValue(_currEncounter->getsect11(index));
    ui->sect12Box->setValue(_currEncounter->getsect12(index));
    ui->sect13Box->setValue(_currEncounter->getsect13(index));
    ui->sect14Box->setValue(_currEncounter->getsect14(index));

}

void MainWindow::on_levelBox_valueChanged(int arg1)
{
    _currEncounter->setLevel( ui->enemySlotBox->currentIndex(), (quint8)arg1 );
}

void MainWindow::on_enemyNameBox_currentIndexChanged(int index)
{
    if(ui->enemySlotBox->currentIndex()>=0)
    //if(ui->enemyNameBox->isEnabled() )
        _currEncounter->setEnemyID(ui->enemySlotBox->currentIndex(), (quint8)index);
}

void MainWindow::on_enabledCheck_stateChanged(int arg1)
{
    bool enable;
    quint8 state = _currEncounter->getEnabledEn();
    arg1 == 0 ? enable = false : enable = true;
    state &= ~_enemymask;
    if(enable) state |= _enemymask;
    _currEncounter->setEnabledEn(state);
}

void MainWindow::on_visibleCheck_stateChanged(int arg1)
{
    bool enable;
    quint8 state = _currEncounter->getVisibleEn();
    arg1 == 0 ? enable = false : enable = true;
    state &= ~_enemymask;
    if(enable) state |= _enemymask;
    _currEncounter->setVisibleEn(state);
}

void MainWindow::on_targetableCheck_stateChanged(int arg1)
{
    bool enable;
    quint8 state = _currEncounter->getTargetableEn();
    arg1 == 0 ? enable = false : enable = true;
    state &= ~_enemymask;
    if(enable) state |= _enemymask;
    _currEncounter->setTargetableEn(state);
}



void MainWindow::on_loadedCheck_stateChanged(int arg1)
{
    bool enable;
    quint8 state = _currEncounter->getLoadedEn();
    arg1 == 0 ? enable = false : enable = true;
    state &= ~_enemymask;
    if(enable) state |= _enemymask;
    _currEncounter->setLoadedEn(state);
}

void MainWindow::on_xCoordBox_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setCoordX(ui->enemySlotBox->currentIndex(),arg1);
}

void MainWindow::on_yCoordBox_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setCoordY(ui->enemySlotBox->currentIndex(),arg1);
}

void MainWindow::on_zCoordBox_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setCoordZ(ui->enemySlotBox->currentIndex(),arg1);
}

void MainWindow::on_sect11Box_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setsect11(ui->enemySlotBox->currentIndex(), arg1);
}

void MainWindow::on_sect12Box_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setsect12(ui->enemySlotBox->currentIndex(), arg1);
}

void MainWindow::on_sect13Box_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setsect13(ui->enemySlotBox->currentIndex(), arg1);
}

void MainWindow::on_sect14Box_valueChanged(int arg1)
{
    if(ui->enemySlotBox->currentIndex()>=0)
        _currEncounter->setsect14(ui->enemySlotBox->currentIndex(), arg1);
}
