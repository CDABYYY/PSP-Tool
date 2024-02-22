#include "PSPAskBug.h"
#include <qformlayout.h>

PSPAskBug::PSPAskBug(QWidget* parent, std::vector<Defects>& defects, int injectphase, double fixtime)
	:datas(defects) ,parent(parent),intime(injectphase),ftime(fixtime)
{
	cType = new QComboBox;
	cInject = new QComboBox;
	cFrom = new QComboBox;

	for (int i = 0; i < 10; i++)cType->addItem(QString::number(i));
	cInject->addItem("计划阶段");
	cInject->addItem("设计阶段");
	cInject->addItem("编码阶段");
	cFrom->addItem("无");
	for (int i = 0; i < defects.size(); i++)cFrom->addItem(defects[i].Description);

	eDescription = new QLineEdit;
	pbComfirm = new QPushButton("确定");
	connect(pbComfirm, SIGNAL(clicked(bool)), this, SLOT(Confirm()));
	QFormLayout* fmain = new QFormLayout(this);
	fmain->addRow("类型", cType);
	fmain->addRow("引入阶段", cInject);
	fmain->addRow("引入由", cFrom);
	fmain->addRow("描述", eDescription);
	fmain->addRow(pbComfirm);
}
void PSPAskBug::Confirm() {
	Defects d;
	ok = true;
	QDate date = QDate::currentDate();
	d.Date = date.month() * 100 + date.day();
	d.Type = cType->currentIndex() * 10;
	d.Inject = cInject->currentIndex();
	d.Remove = intime;
	d.FixTime = ftime;
	d.Description = eDescription->text();
	d.FixDefect = 0;
	datas.push_back(d);
	if (cFrom->currentIndex())
		datas[cFrom->currentIndex() - 1].FixDefect++;
	close();
}