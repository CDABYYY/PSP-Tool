#include <vector>
#include "WriteWord.h"
#include "YData.h"


QAxObject* WriteWord::word = nullptr;
QAxObject* WriteWord::document = nullptr;
QAxObject* WriteWord::documents = nullptr;
QAxObject* WriteWord::allBookmarks = nullptr;
int WriteWord::readBookmark = 1;

QString PhaseName0[7] = { "计划阶段","设计阶段" ,"编码阶段" ,"复查阶段" ,"编译阶段" ,"测试阶段" ,"报告阶段" };
void WriteWord::StartWord(QString s) {
	word = new QAxObject();
	word->setControl("word.Application");
	word->setProperty("Visible", false);
	documents = word->querySubObject("Documents");
	documents->dynamicCall("Add(QString)", s);
	document = word->querySubObject("ActiveDocument");
	allBookmarks = document->querySubObject("Bookmarks");
	readBookmark = 1;
}
void WriteWord::SaveClose(QString s)
{
	document->dynamicCall("SaveAs(const QString&)", s);
	document->dynamicCall("Close(boolean)", false);
	word->dynamicCall("Quit()");
}
void WriteWord::ReadBookmark(QString s)
{
	QAxObject* bookmark = allBookmarks->querySubObject("Item(QVariant)", readBookmark);
	bookmark->dynamicCall("Select(void)");
	if(s != "")
		bookmark->querySubObject("Range")->setProperty("Text", s);
	readBookmark++;
}
void WriteWord::MoveRight(QString s, int i) {
	QAxObject* selection = word->querySubObject("Selection");
	if (!selection) return;
	selection->dynamicCall("TypeText(const QString&)", s);
	//selection->dynamicCall("SetText(QString)", name);
	selection->dynamicCall("MoveRight(int)", i);
}
void WriteWord::WriteWord1(std::vector<int> v) {
	StartWord(QString("D:/QT/Programs/PSP Tool/Templates/1.dotx"));
	ReadBookmark(TD.StudentName);
	QDate date = QDate::currentDate();
	int dt = date.month() * 100 + date.day();
	QString s0 = QString::asprintf("%02d/%02d", dt / 100, dt % 100);
	ReadBookmark(s0);
	ReadBookmark(TD.InstrucorName);
	ReadBookmark(TD.ClassName);
	ReadBookmark();
	for (size_t i = 0; i < TD.Datas1.size(); i++)
	{
		const E1Datas& d = TD.Datas1[i];
		bool ok = true;
		for (auto& j : v)if (d.PartName == TD.Finished[j].DataName)ok = false;
		if (ok)continue;
		QString s1 = QString::asprintf("%02d/%02d", d.Date / 100, d.Date % 100);
		MoveRight(s1);
		int i2 = d.StartTime;
		QString s2 = QString::asprintf("%02d:%02d", i2 / 100, i2 % 100);
		MoveRight(s2);
		int i3 = d.StopTime;
		QString s3 = QString::asprintf("%02d:%02d", i3 / 100, i3 % 100);
		MoveRight(s3);
		QString s4 = QString::number((int)d.InterruptTime);
		MoveRight(s4);
		int i5 = d.StopTime - d.StartTime - d.InterruptTime;
		QString s5 = QString::number(i5);
		MoveRight(s5);
		QString s6 = QString::asprintf("Programming #%d", d.ID);
		MoveRight(s6);
		QString s7 = d.PartName;
		MoveRight(s7);
		QString s8("");
		if (d.Finished)s8 = "X";
		MoveRight(s8);
		QString s9 = QString::number(d.Units);
		MoveRight(s9, 2);
	}
	SaveClose(QString("D:/QT/Programs/PSP Tool/Outputs/Out10.docx"));
}
void WriteWord::WriteWord2(std::vector<int> v) {
	StartWord(QString("D:/QT/Programs/PSP Tool/Templates/2.dotx"));
	ReadBookmark(TD.StudentName);
	QDate date = QDate::currentDate();
	ReadBookmark(QString::asprintf("%02d/%02d", date.month(), date.day()));
	for (auto &i:v) {
		const E2Datas& d2 = TD.Finished[i];
		ReadBookmark(QString::number(d2.dataID));
		ReadBookmark();
		MoveRight(QString::asprintf("%02d/%02d", d2.BeginDate / 100, d2.BeginDate % 100));
		MoveRight(QString("Programming"));
		for (int i0 = 0; i0 < 10; i0++) {
			if (d2.E1Results[i0] > 0) {
				if (d2.E1Results[i0] == (int)d2.E1Results[i0])
					MoveRight(QString::number((int)d2.E1Results[i0]));
				else
					MoveRight(QString::asprintf("%.2lf", d2.E1Results[i0]));
			}
			else MoveRight("");
		}
		ReadBookmark(d2.DataName);
	}
	SaveClose(QString("D:/QT/Programs/PSP Tool/Outputs/Out20.docx"));
}
void WriteWord::WriteWord3(int choosed) {
	StartWord(QString("D:/QT/Programs/PSP Tool/Templates/3.dotx"));
	E2Datas& d = TD.Finished[choosed];
	ReadBookmark(TD.StudentName);
	ReadBookmark(QString::asprintf("%02d/%02d", d.BeginDate / 100, d.BeginDate % 100));
	ReadBookmark(TD.InstrucorName);
	ReadBookmark(QString::number(d.dataID));
	for (int i = 0; i < d.DefectData.size(); i++) {
		const Defects& d0 = d.DefectData[i];
		ReadBookmark();
		MoveRight(QString::asprintf("%02d/%02d", d0.Date / 100, d0.Date % 100), 2);
		MoveRight("");
		MoveRight(QString::number(i + 1), 2);
		MoveRight("");
		MoveRight(QString::number(d0.Type), 2);
		MoveRight("");
		MoveRight(PhaseName0[d0.Inject], 2);
		MoveRight("");
		MoveRight(PhaseName0[d0.Remove], 2);
		MoveRight("");
		MoveRight(QString::asprintf("%.2lf", d0.FixTime), 2);
		MoveRight("");
		MoveRight(QString::number(d0.FixDefect), 2);
		ReadBookmark(d0.Description);
	}
	SaveClose(QString::asprintf("D:/QT/Programs/PSP Tool/Outputs/Out3%d.docx",choosed));
}
void WriteWord::WriteWord4(int choosed) {
	StartWord(QString("D:/QT/Programs/PSP Tool/Templates/4.dotx"));
	E2Datas& d = TD.Finished[choosed];
	ReadBookmark(TD.StudentName);
	ReadBookmark(QString::asprintf("%02d/%02d", d.BeginDate / 100, d.BeginDate % 100));
	ReadBookmark(d.DataName);
	ReadBookmark(QString::number(d.dataID));
	ReadBookmark(TD.InstrucorName);
	ReadBookmark(d.Language);
	for (int i = 0; i < 87; i++) {
		if (d.E2Results[i] > 0) {
			if (d.E2Results[i] == (int)d.E2Results[i])
				ReadBookmark(QString::number((int)d.E2Results[i]));
			else 
				ReadBookmark(QString::asprintf("%.2lf", d.E2Results[i]));
		}
		else ReadBookmark();
	}
	SaveClose(QString::asprintf("D:/QT/Programs/PSP Tool/Outputs/Out4%d.docx",choosed));
}

void WriteWord::AppendWord(int i0,int i1)
{
	QAxObject* wordrange = document->querySubObject("Content");
	QAxObject* pobj = wordrange->querySubObject("Paragraphs");
	QAxObject* nobj = pobj->querySubObject("Last")->querySubObject("Range");
	nobj->dynamicCall("InsertFile(QString)", QString::asprintf("D:/QT/Programs/PSP Tool/Outputs/Out%d%d.docx", i0,i1));
	wordrange->dynamicCall("InsertParagraphAfter(void)");
}
void WriteWord::MergeAll(std::vector<int> v, int op[4])
{
	word = new QAxObject();
	word->setControl("word.Application");
	word->setProperty("Visible", false);
	documents = word->querySubObject("Documents");
	documents->dynamicCall("Add(QString)", QString("D:/QT/Programs/PSP Tool/Templates/0.docx"));
	document = word->querySubObject("ActiveDocument");
	if (op[0])AppendWord(1,0);
	if(op[1])AppendWord(2,0);
	if (op[2])for (auto& i : v)AppendWord(3, i);
	if(op[3])for (auto& i : v)AppendWord(4, i);

	SaveClose(QString("D:/QT/Programs/PSP Tool/Outputs/OutPut.docx"));
}
