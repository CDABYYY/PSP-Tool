#pragma once
#include <qwidget.h>
#include<qlineedit.h>
#include<qpushbutton.h>
#include<qformlayout.h>
#include<vector>
#include"YData.h"
#include"PSPTool.h"
class PSPAskProject :
    public QWidget
{
    Q_OBJECT
public slots:
    void askProject();
    void closeEvent (QCloseEvent*) override;
public:
    PSPAskProject(PSPTool* parent);
    QLineEdit* projectName;
    PSPTool* parent;
    QLineEdit* projectLanguage;
    QLineEdit* planUnits;
    QPushButton* confirmButton;
    bool showmain;
};

