#pragma once
#include <qwidget.h>
#include "YData.h"
#include <qtimer.h>
#include <QTime>
#include <qlcdnumber.h>
#include <qpushbutton.h>
#include <QLabel>
#include <qmenu.h>
#include <qsystemtrayicon.h>
#include "WinKeyHook.h"
#include "PSPAskBug.h"
#include "PSPTool.h"

//extern QString PhaseName[7];
class PSPTimer :
    public QWidget
{
    Q_OBJECT
public slots:
    void updataTimeAndDisplay();
    void bpInterrupted();
    void bpDebug();
    void bpNext();
    void bpLast();
    void bpHome();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
public:
    PSPTimer(PSPTool* parent, int datanum);
    ~PSPTimer();
    void closeEvent(QCloseEvent* event)override;
    void hideEvent(QHideEvent* event)override;
    void pressKey(int key);
    void releaseKey(int key);
    void updatePhaseData(int);

    bool readyclose = false;
    int keyStatus = 0;

    PSPTool* parent;
    E2Datas& datas;
    int datasnum;

    QTime startTime;
    double interruptTime;

    QTimer* ptimer;  //定时器对象
    QTime baseTime;  //时间对象——00:00:00
    QString showStr;  //lcdNumber的时刻值	

    QLabel* projectName, * projectLanguage, * phaseName;
    QLCDNumber* lcdNumber;
    QPushButton* interrupted, * debug, * next, * last, * home;

    QSystemTrayIcon* trayIcon;
    QMenu* trayIconMenu;
    //窗口管理动作
    QAction* Ainterrupted;
    QAction* Adebug;
    QAction* Anext;
    QAction* Alast;
    QAction* Ahome;
    QAction* Aquit;
};

