#pragma once
#include <qwidget.h>
#include <QDialog>
#include "PSPTimer.h"
#include "PSPTool.h"
class PSPHelpTimer:public QDialog {
	Q_OBJECT
public slots:
	void build() {
		PSPTimer* t = new PSPTimer(parent, num);
		parent->hide();
		t->show();
	}
public:
	PSPHelpTimer(PSPTool* parent, int num) :parent(parent), num(num) {};
	PSPTool* parent;
	int num;
};