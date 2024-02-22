#pragma once
#include <qwidget.h>
#include <qlineedit.h>
#include <QPushButton>
class PSPAskInfo :
    public QWidget
{
    Q_OBJECT
public slots:
    void confirm();

public:
    PSPAskInfo();
    QLineEdit* qname, * qinstructor, * qclass;
    QPushButton* pb;
};

