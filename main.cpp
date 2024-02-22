#include "PSPTool.h"
#include <QtWidgets/QApplication>
#include "YData.h"
#include "WriteWord.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app = &a;
    TotalData::getDatas();
    PSPTool::updateFinished();
    PSPTool w;
    w.show();
    return a.exec();
}
