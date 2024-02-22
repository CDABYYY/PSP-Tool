#pragma once

#include <QtWidgets/QWidget>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qstackedwidget.h>
#include <qtabwidget.h>
#include <qscrollarea.h>
#include <qlabel.h>
#include "PSPAskInfo.h"
#include "PSPOutput.h"
#include "ui_PSPTool.h"

extern QApplication* app;

class PSPTool : public QWidget
{
    Q_OBJECT
public slots:
    void buildTimer();
    void getinfo() {
        auto a = new PSPAskInfo();
        a->show();
    }
    void getOutput() {
        auto a = new PSPOutput();
        a->show();
    }
public:
    PSPTool(QWidget *parent = nullptr);
    ~PSPTool();
    void updateUnfinished();
    static void updateFinished();
    void closeEvent(QCloseEvent*)override;
    QLabel* className, * studentName, * instructorName;
    QPushButton * openFile, * newProject, * exportWord;
    QScrollArea* projects;

private:
    //Ui::PSPToolClass ui;
};
