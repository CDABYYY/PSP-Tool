#include "PSPAskProject.h"
#include <QCloseEvent>
#include "PSPTimer.h"

PSPAskProject::PSPAskProject(PSPTool* parent):parent(parent) {
    showmain = true;
    projectName = new QLineEdit();
    projectLanguage = new QLineEdit();
    planUnits = new QLineEdit();
    confirmButton = new QPushButton("确定");
    connect(confirmButton, SIGNAL(clicked(bool)), this, SLOT(askProject()));

    QFormLayout* fbox = new QFormLayout(this);
    fbox->addRow("项目名称", projectName);
    fbox->addRow("使用语言", projectLanguage);
    fbox->addRow("代码行数预估", planUnits);
    fbox->addRow(confirmButton);
}
void PSPAskProject::askProject() {
    E2Datas newe;
    newe.DataName = projectName->text();
    newe.Language = projectLanguage->text();
    newe.PlanUnits = planUnits->text().toInt();
    newe.Phase = 0;
    QDate cdate = QDate::currentDate();
    newe.BeginDate = cdate.month() * 100 + cdate.day();
    newe.TotalUnits = 0;
    newe.dataID = TD.UnFinished.size() + TD.Finished.size() + 1;
    for (int i = 0; i < 7; i++)
        newe.PhaseTime[i] = 0;
    TD.UnFinished.push_back(newe);


    PSPTimer *ht = new PSPTimer(parent, TD.UnFinished.size() - 1);
    ht->show();
    showmain = false;
    close();
}
void PSPAskProject::closeEvent(QCloseEvent* e) {
    if (showmain)parent->show();
    e->accept();
}
