#include "PSPTimer.h"
#include "YData.h"
#include "PSPTool.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qevent.h>
#include <QInputDialog>

QString PhaseName[7]={ "计划阶段","设计阶段" ,"编码阶段" ,"复查阶段" ,"编译阶段" ,"测试阶段" ,"报告阶段" };

PSPTimer::PSPTimer(PSPTool* parent, int datanum)
	:datas(TD.UnFinished[datanum]),parent(parent),datasnum(datanum)
{
	QVBoxLayout* mainbox = new QVBoxLayout(this);
	QHBoxLayout* hbox1, *hbox2;
	projectName = new QLabel(datas.DataName);
	projectLanguage = new QLabel(datas.Language);
	phaseName = new QLabel(PhaseName[datas.Phase]);
	hbox1 = new QHBoxLayout;
	hbox1->addWidget(projectName);
	hbox1->addWidget(projectLanguage);
	hbox1->addWidget(phaseName);
	mainbox->addLayout(hbox1);

	
	lcdNumber = new QLCDNumber;
	lcdNumber->setFixedSize(600, 150);
	lcdNumber->setDigitCount(5);
	mainbox->addWidget(lcdNumber);

	interrupted = new QPushButton("中断");
	debug = new QPushButton("报告BUG");
	next = new QPushButton("下一阶段");
	last = new QPushButton("上一阶段");
	hbox2 = new QHBoxLayout;
	hbox2->addWidget(interrupted);
	hbox2->addWidget(debug);
	hbox2->addWidget(next);
	hbox2->addWidget(last);
	mainbox->addLayout(hbox2);

	home = new QPushButton("回到主菜单");
	mainbox->addWidget(home);


	connect(interrupted, SIGNAL(clicked(bool)), this, SLOT(bpInterrupted()));
	connect(debug, SIGNAL(clicked(bool)), this, SLOT(bpDebug()));
	connect(next, SIGNAL(clicked(bool)), this, SLOT(bpNext()));
	connect(last, SIGNAL(clicked(bool)), this, SLOT(bpLast()));
	connect(home, SIGNAL(clicked(bool)), this, SLOT(bpHome()));

	//后台相关
	QIcon icon = QIcon("D:/QT/Programs/Study_VS_QT_2/2.png");
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setToolTip("Timing");
	trayIcon->show();

	Ainterrupted = new QAction("中断(Ctrl + 0 + 1)", this);
	Adebug = new QAction("报告BUG(Ctrl + 0 + 2)", this);
	Anext = new QAction("下一阶段(Ctrl + 0 + 3)", this);
	Alast = new QAction("上一阶段(Ctrl + 0 + 4)", this);
	Ahome = new QAction("回到主菜单(Ctrl + 0 + 5)", this);
	Aquit = new QAction("退出", this);
	connect(Ainterrupted, SIGNAL(triggered()), this, SLOT(bpInterrupted()));
	connect(Adebug, SIGNAL(triggered()), this, SLOT(bpDebug()));
	connect(Anext, SIGNAL(triggered()), this, SLOT(bpNext()));
	connect(Alast, SIGNAL(triggered()), this, SLOT(bpLast()));
	connect(Ahome, SIGNAL(triggered()), this, SLOT(bpHome()));
	connect(Aquit, SIGNAL(triggered()), app, SLOT(quit()));

	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(Ainterrupted);
	trayIconMenu->addAction(Adebug);
	trayIconMenu->addAction(Anext);
	trayIconMenu->addAction(Alast);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(Ahome);
	trayIconMenu->addAction(Aquit);
	trayIcon->setContextMenu(trayIconMenu);

	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	//HOOK
	static WinKeyHook keyboard;
	keyboard.SetKeyPressCallBack(std::bind(&PSPTimer::pressKey, this,std::placeholders::_1));
	keyboard.SetKeyReleaseCallBack(std::bind(&PSPTimer::releaseKey, this, std::placeholders::_1));
	
	ptimer = new QTimer();
	baseTime = QTime::currentTime();
	updatePhaseData(datas.Phase);
	ptimer->start(1000);
	connect(ptimer, SIGNAL(timeout()), this, SLOT(updataTimeAndDisplay()));

	startTime = QTime::currentTime();
	interruptTime = 0;
	trayIcon->showMessage("PSP Tool", "Open");
}


PSPTimer::~PSPTimer() {
	parent->show();
}

void PSPTimer::closeEvent(QCloseEvent* event) {
	if (trayIcon->isVisible()) {
		trayIcon->showMessage("PSP Tool", "Hide");
		hide();
		event->ignore();
	}
	if (readyclose) {
		int s = QInputDialog::getInt(this, "单元统计","本次完成的单元数");
		datas.TotalUnits += s;

		if (interrupted->text() == "继续")
			bpInterrupted();
		E1Datas e1;
		QDate date = QDate::currentDate();
		e1.Date = date.month() * 100 + date.day();
		e1.StartTime = startTime.hour() * 60 + startTime.minute();
		QTime nt = QTime::currentTime();
		e1.StopTime = nt.hour() * 60 + nt.minute();
		e1.InterruptTime = interruptTime;
		e1.Units = s;
		e1.PartName = datas.DataName;
		TD.Datas1.push_back(e1);

		parent->updateUnfinished();
		parent->show();
		event->accept();
	}
}

void PSPTimer::hideEvent(QHideEvent* event) {
	if (trayIcon->isVisible()) {
		hide();
		event->ignore();
	}
}


void PSPTimer::iconActivated(QSystemTrayIcon::ActivationReason reason) {
	if (reason == QSystemTrayIcon::DoubleClick)
		this->show();
}


void PSPTimer::updataTimeAndDisplay() {
	QTime current = QTime::currentTime();//获取系统当前时间
	int t = this->baseTime.msecsTo(current);  //两者相减的时间之差
	QTime showtime(0, 0, 0, 0);//初始时间
	showtime = showtime.addMSecs(t);//增加tms
	showStr = showtime.toString("mm:ss"); //转换为string类型
	lcdNumber->display(showStr);
	trayIcon->setToolTip(showStr);
}
void PSPTimer::bpInterrupted() {
	static QTime pauseTime;  //暂停时间【静态】
	if (interrupted->text() == "中断") {
		trayIcon->showMessage("PSP Tool", "Interrupt");

		pauseTime = QTime::currentTime();//获取点击暂停时的当前时间
		ptimer->stop();
		interrupted->setText("继续");
		Ainterrupted->setText("继续");
		debug->setEnabled(false);
		next->setEnabled(false);//开始按钮无法点击
		last->setEnabled(false);
	}
	else {
		trayIcon->showMessage("PSP Tool", "Continue");

		QTime cut = QTime::currentTime();//继续时的时间
		int t = pauseTime.secsTo(cut);//差值
		baseTime = baseTime.addSecs(t);  //后延相应的tms继续计时
		ptimer->start(1);
		interrupted->setText("中断");
		Ainterrupted->setText("中断");
		debug->setEnabled(true);
		next->setEnabled(true);//开始按钮可以点击
		last->setEnabled(true);
	}
}
void PSPTimer::bpDebug() {
	static QTime pauseTime;  //暂停时间【静态】
	if (debug->text() == "报告BUG") {
		trayIcon->showMessage("PSP Tool", "Debug");

		pauseTime = QTime::currentTime();//获取点击暂停时的当前时间
		debug ->setText("修复完成");
		Adebug->setText("修复完成");
		next->setEnabled(false);//开始按钮无法点击
		last->setEnabled(false);
	}
	else {
		QTime cut = QTime::currentTime();//继续时的时间
		double t = (double)pauseTime.secsTo(cut) / 60;//差值
		interruptTime += t;
		PSPAskBug ab(this, datas.DefectData, datas.Phase, t);
		ab.exec();
		if(ab.ok)
		{
			trayIcon->showMessage("PSP Tool", "Finished");

			debug->setText("报告BUG");
			Adebug->setText("报告BUG");
			next->setEnabled(true);//开始按钮可以点击
			next->setEnabled(true);
		}
	}
}
void PSPTimer::bpNext() {
	if (datas.Phase == 6) {
		double t = baseTime.secsTo(QTime::currentTime());
		double mins = t / 60;
		datas.PhaseTime[datas.Phase] = mins;
		datas.Phase++;
		readyclose = true;
		close();
	}else
	{
		updatePhaseData(datas.Phase + 1);
	}
}
void PSPTimer::bpLast() {
	trayIcon->showMessage("PSP Tool", "Next");
	updatePhaseData(datas.Phase - 1);
}
void PSPTimer::bpHome() {
	trayIcon->showMessage("PSP Tool", "Home");
	readyclose = true;
	close();
}

void PSPTimer::pressKey(int key) {
	if (key == 162)keyStatus |= 1;
	if (key == 96)keyStatus |= 2;

	if (keyStatus == 3) {
		if (key == 97)bpInterrupted();
		if (key == 98)bpDebug();
		if (key == 99)bpNext();
		if (key == 100)bpLast();
		if (key == 101)bpHome();
	}
	projectName->setText(QString::number(keyStatus));
	projectLanguage->setText(QString::number(key));
}

void PSPTimer::releaseKey(int key) {
	if (key == 162)keyStatus &= 2;
	if(key == 96)keyStatus &= 1;
}

void PSPTimer::updatePhaseData(int toPhase)
{
	double t = baseTime.secsTo(QTime::currentTime());
	double mins = t / 60;
	datas.PhaseTime[datas.Phase] += mins;

	datas.Phase = toPhase;

	phaseName->setText(PhaseName[datas.Phase]);
	int ps = datas.PhaseTime[datas.Phase] * 60;
	baseTime = QTime::currentTime();
	baseTime = baseTime.addSecs(-ps);
	if (datas.Phase == 6)next->setText("完成项目");
	else next->setText("下一阶段");
	if (datas.Phase == 0)last->setEnabled(false);
	else last->setEnabled(true);
	if (datas.Phase < 3)debug->setEnabled(false);
	else debug->setEnabled(true);
}
