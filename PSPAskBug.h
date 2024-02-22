#pragma once
#include <QDialog>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "YData.h"
class PSPAskBug :
    public QDialog
{
    Q_OBJECT
public slots:
    void Confirm();
public:
    PSPAskBug(QWidget*, std::vector<Defects>&, int, double);
    QWidget* parent;
    std::vector<Defects>& datas;
    int intime;
    double ftime;
    bool ok = false;
    QComboBox* cType, *cInject, *cFrom;
    QLineEdit* eDescription;
    QPushButton* pbComfirm;
};

