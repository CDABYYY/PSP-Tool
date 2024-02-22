#include "PSPOutput.h"
#include <QVBoxLayout>
#include <qscrollarea.h>
#include "YData.h"
#include "WriteWord.h"
PSPOutput::PSPOutput() {
	auto mainbox = new QVBoxLayout(this);
	auto cbox = new QHBoxLayout();
	for (int i = 0; i < 4; i++)outputs[i] = new QRadioButton(QString::asprintf("Part%d", i + 1));
	outputs[4] = new QRadioButton("合并");
	for (int i = 0; i < 5; i++) {
		cbox->addWidget(outputs[i]);
		outputs[i]->setChecked(true);
	}
	auto s = new QScrollArea();
	auto w = new QWidget();
	auto hb = new QVBoxLayout(w);
	for (auto& e : TD.Finished)
	{
		auto t = new QRadioButton(e.DataName);
		projects.push_back(t);
		hb->addWidget(t);
	}
	s->setWidget(w);
	mainbox->addWidget(s);
	mainbox->addLayout(cbox);
	pb = new QPushButton("导出");
	mainbox->addWidget(pb);
	connect(pb, SIGNAL(clicked(bool)), this, SLOT(output()));

}
void PSPOutput::output() {
	std::vector<int> choosed;
	int i0 = 0;
	for (auto& p : projects) {
		if (p->isChecked())choosed.push_back(i0);
		i0++;
	}
	if (outputs[0]->isChecked())WriteWord::WriteWord1();
	if (outputs[1]->isChecked())WriteWord::WriteWord2();
	for (auto& i : choosed) {
		if (outputs[2]->isChecked())WriteWord::WriteWord3(i);
		if (outputs[3]->isChecked())WriteWord::WriteWord4(i);
	}
	if (outputs[4]->isChecked())WriteWord::MergeAll();
	this->close();
}