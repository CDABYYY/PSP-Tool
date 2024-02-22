#include "PSPTool.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include "PSPAskProject.h"
#include "PSPHelpTimer.h"
QApplication* app = nullptr;
PSPTool::PSPTool(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainbox = new QVBoxLayout(this);
    QHBoxLayout* hbox1 = new QHBoxLayout;
    QHBoxLayout* hbox2 = new QHBoxLayout;
    QVBoxLayout* vbox1 = new QVBoxLayout;
    className = new QLabel(TD.ClassName);
    studentName = new QLabel(TD.StudentName);
    instructorName = new QLabel(TD.InstrucorName);
    hbox1->addWidget(className);
    hbox1->addWidget(studentName);
    hbox1->addWidget(instructorName);
    openFile = new QPushButton("修改信息");
    newProject = new QPushButton("新建项目");
    exportWord = new QPushButton("导出Word");
    vbox1->addWidget(openFile);
    vbox1->addWidget(newProject);
    vbox1->addWidget(exportWord);
    projects = new QScrollArea;
    hbox2->addLayout(vbox1);
    hbox2->addWidget(projects);
    mainbox->addLayout(hbox1);
    mainbox->addLayout(hbox2);
    //ui.setupUi(this);

    updateUnfinished();
    connect(openFile, SIGNAL(clicked(bool)), this, SLOT(getinfo()));
    connect(newProject, SIGNAL(clicked(bool)), this, SLOT(buildTimer()));
    connect(exportWord, SIGNAL(clicked(bool)), this, SLOT(getOutput()));
}

PSPTool::~PSPTool()
{}

void PSPTool::updateUnfinished()
{
    QWidget* w = new QWidget;
    QVBoxLayout *hb = new QVBoxLayout(w);
    for (int i = 0; i < TD.UnFinished.size(); i++) {
        if (TD.UnFinished[i].Phase == 7) {
            TD.UnFinished[i].TotalTimes = 0;
            for (int i0 = 0; i < 7; i++)
                TD.UnFinished[i].TotalTimes += TD.UnFinished[i].PhaseTime[i0];
            TD.Finished.push_back(TD.UnFinished[i]);
            TD.UnFinished.erase(TD.UnFinished.begin() + i);
            i--;
            continue;
        }
        QPushButton* tpb = new QPushButton(TD.UnFinished[i].DataName);
        PSPHelpTimer* tht = new PSPHelpTimer(this, i);
        connect(tpb, SIGNAL(clicked(bool)), tht, SLOT(build()));
        hb->addWidget(tpb);
    }
    projects->setWidget(w);

}

void PSPTool::updateFinished()
{
    TD.MaxUnit = 0;
    TD.MinUnit = 0;
    TD.TotalTimes = 0;
    TD.TotalUnits = 0;
    TD.MaxRate = 0;
    TD.MinRate = 999;
    for (int i = 0; i < 7; i++)
        TD.PhaseTime[i] = 0;
    for (int i = 0; i < 6; i++)
        TD.DefectData[i] = 0;
    
    for (int i = 0; i < TD.Finished.size(); i++)
        TD.getResults(TD.Finished[i]);
}

void PSPTool::closeEvent(QCloseEvent* e)
{
    TotalData::saveDatas();
    e->accept();
}

void PSPTool::buildTimer() {
    PSPAskProject* ask = new PSPAskProject(this);
    ask->show();
    this->hide();
}