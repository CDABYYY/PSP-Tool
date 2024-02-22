#include "PSPAskInfo.h"
#include <QLabel>
#include <qformlayout.h>
#include "YData.h"

PSPAskInfo::PSPAskInfo() {
	qname = new QLineEdit;
	qinstructor = new QLineEdit;
	qclass = new QLineEdit;
	auto mainbox = new QFormLayout(this);
	mainbox->addRow("姓名", qname);
	mainbox->addRow("指导老师", qinstructor);
	mainbox->addRow("班级", qclass);
	pb = new QPushButton("确认");
	mainbox->addRow(pb);
	connect(pb, SIGNAL(clicked(bool)), this, SLOT(confirm()));
}

void PSPAskInfo::confirm() {
	TD.StudentName = qname->text();
	TD.InstrucorName = qinstructor->text();
	TD.ClassName = qclass->text();
	this->close();
}