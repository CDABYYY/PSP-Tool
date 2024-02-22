#pragma once
#include <qwidget.h>
#include <qobject.h>
#include <vector>
#include <qradiobutton.h>
#include <qpushbutton.h>
class PSPOutput :
    public QWidget
{
    Q_OBJECT
public slots:
    void output();
public:
    PSPOutput();
    std::vector<QRadioButton*> projects;
    QRadioButton* outputs[5];
    QPushButton* pb;
};

