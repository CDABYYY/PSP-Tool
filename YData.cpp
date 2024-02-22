#include "YData.h"
#include <QFile>
using namespace std;

TotalData TD;
QJsonObject E1Datas::writeJson() {
	QJsonObject rootobj;
	rootobj.insert("Date", Date);
	rootobj.insert("StartTime", StartTime);
	rootobj.insert("StopTime", StopTime);
	rootobj.insert("InterruptTime", InterruptTime);
	rootobj.insert("Units", Units);
	rootobj.insert("ID", ID);
	rootobj.insert("Finished", Finished);
	rootobj.insert("PartName", PartName);
	return rootobj;
}
void E1Datas::readJson(QJsonValue jsonvalue) {
	if (jsonvalue.type() == QJsonValue::Object) {
		QJsonObject rootobj = jsonvalue.toObject();
		Date = rootobj.value("Date").toInt();
		StartTime = rootobj.value("StartTime").toDouble();
		StopTime = rootobj.value("StopTime").toDouble();
		InterruptTime = rootobj.value("InterruptTime").toDouble();
		Units = rootobj.value("Units").toInt();
		ID = rootobj.value("ID").toInt();
		Finished = rootobj.value("Finished").toBool();
		PartName = rootobj.value("PartName").toString();
	}
}

QJsonObject Defects::writeJson() {
	QJsonObject rootobj;
	rootobj.insert("Date", Date);
	rootobj.insert("Type", Type);
	rootobj.insert("Inject", Inject);
	rootobj.insert("Remove", Remove);
	rootobj.insert("FixTime", FixTime);
	rootobj.insert("FixDefect", FixDefect);
	rootobj.insert("Description", Description);
	return rootobj;
}
void Defects::readJson(QJsonValue jsonvalue) {
	if (jsonvalue.type() == QJsonValue::Object) {
		QJsonObject rootobj = jsonvalue.toObject();
		Date = rootobj.value("Date").toInt();
		Type = rootobj.value("Type").toInt();
		Inject = rootobj.value("Inject").toInt();
		Remove = rootobj.value("Remove").toInt();
		FixTime = rootobj.value("FixTime").toDouble();
		FixDefect = rootobj.value("FixDefect").toInt();
		Description = rootobj.value("Description").toString();
	}
}

QJsonObject E2Datas::writeJson() {
	QJsonObject rootobj;
	rootobj.insert("dataID", dataID);
	rootobj.insert("TotalTimes", TotalTimes);
	rootobj.insert("TotalUnits", TotalUnits);
	rootobj.insert("PlanUnits", PlanUnits);
	rootobj.insert("DataName", DataName);
	rootobj.insert("Language", Language);
	rootobj.insert("BeginDate", BeginDate);
	rootobj.insert("Phase", Phase);
	QJsonArray PhaseTimearray;
	for (int i = 0; i < 7; i++)
		PhaseTimearray.append(PhaseTime[i]);
	rootobj.insert("PhaseTime", PhaseTimearray);
	QJsonArray DefectDataarray;
	for (int i = 0; i < DefectData.size(); i++)
		DefectDataarray.append(DefectData[i].writeJson());
	rootobj.insert("DefectData", DefectDataarray);
	return rootobj;
}
void E2Datas::readJson(QJsonValue jsonvalue) {
	if (jsonvalue.type() == QJsonValue::Object) {
		QJsonObject rootobj = jsonvalue.toObject();
		dataID = rootobj.value("dataID").toInt();
		TotalTimes = rootobj.value("TotalTimes").toDouble();
		TotalUnits = rootobj.value("TotalUnits").toInt();
		PlanUnits = rootobj.value("PlanUnits").toInt();
		DataName = rootobj.value("DataName").toString();
		Language = rootobj.value("Language").toString();
		BeginDate = rootobj.value("BeginDate").toInt();
		Phase = rootobj.value("Phase").toInt();
		QJsonArray PhaseTimearray = rootobj.value("PhaseTime").toArray();
		for (int i = 0; i < PhaseTimearray.size(); i++)
			PhaseTime[i] = PhaseTimearray.at(i).toDouble();
		QJsonArray DefectDataarray = rootobj.value("DefectData").toArray();
		DefectData.resize(DefectDataarray.size());
		for (int i = 0; i < DefectDataarray.size(); i++)
			DefectData[i].readJson(DefectDataarray.at(i));
	}
}

QJsonObject TotalData::writeJson() {
	QJsonObject rootobj;
	QJsonArray Datas1array;
	for (int i = 0; i < Datas1.size(); i++)
		Datas1array.append(Datas1[i].writeJson());
	rootobj.insert("Datas1", Datas1array);
	QJsonArray Finishedarray;
	for (int i = 0; i < Finished.size(); i++)
		Finishedarray.append(Finished[i].writeJson());
	rootobj.insert("Finished", Finishedarray);
	QJsonArray UnFinishedarray;
	for (int i = 0; i < UnFinished.size(); i++)
		UnFinishedarray.append(UnFinished[i].writeJson());
	rootobj.insert("UnFinished", UnFinishedarray);
	rootobj.insert("TotalTimes", TotalTimes);
	rootobj.insert("TotalUnits", TotalUnits);
	QJsonArray PhaseTimearray;
	for (int i = 0; i < 7; i++)
		PhaseTimearray.append(PhaseTime[i]);
	rootobj.insert("PhaseTime", PhaseTimearray);
	QJsonArray DefectDataarray;
	for (int i = 0; i < 6; i++)
		DefectDataarray.append(DefectData[i]);
	rootobj.insert("DefectData", DefectDataarray);
	rootobj.insert("MaxUnit", MaxUnit);
	rootobj.insert("MinUnit", MinUnit);
	rootobj.insert("StudentName", StudentName);
	rootobj.insert("InstrucorName", InstrucorName);
	rootobj.insert("ClassName", ClassName);
	return rootobj;
}
void TotalData::readJson(QJsonValue jsonvalue) {
	if (jsonvalue.type() == QJsonValue::Object) {
		QJsonObject rootobj = jsonvalue.toObject();
		QJsonArray Datas1array = rootobj.value("Datas1").toArray();
		Datas1.resize(Datas1array.size());
		for (int i = 0; i < Datas1array.size(); i++)
			Datas1[i].readJson(Datas1array.at(i));
		QJsonArray Finishedarray = rootobj.value("Finished").toArray();
		Finished.resize(Finishedarray.size());
		for (int i = 0; i < Finishedarray.size(); i++)
			Finished[i].readJson(Finishedarray.at(i));
		QJsonArray UnFinishedarray = rootobj.value("UnFinished").toArray();
		UnFinished.resize(UnFinishedarray.size());
		for (int i = 0; i < UnFinishedarray.size(); i++)
			UnFinished[i].readJson(UnFinishedarray.at(i));
		TotalTimes = rootobj.value("TotalTimes").toDouble();
		TotalUnits = rootobj.value("TotalUnits").toInt();
		QJsonArray PhaseTimearray = rootobj.value("PhaseTime").toArray();
		for (int i = 0; i < PhaseTimearray.size(); i++)
			PhaseTime[i] = PhaseTimearray.at(i).toDouble();
		QJsonArray DefectDataarray = rootobj.value("DefectData").toArray();
		for (int i = 0; i < DefectDataarray.size(); i++)
			DefectData[i] = DefectDataarray.at(i).toInt();
		MaxUnit = rootobj.value("MaxUnit").toInt();
		MinUnit = rootobj.value("MinUnit").toInt();
		StudentName = rootobj.value("StudentName").toString();
		InstrucorName = rootobj.value("InstrucorName").toString();
		ClassName = rootobj.value("ClassName").toString();
	}
}

void TotalData::getDatas()
{
	QFile file("D:/QT/Programs/PSP Tool/Resource/Datas.json");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	TD.readJson(QJsonDocument::fromJson(file.readAll()).object());
	file.close();
}

void TotalData::saveDatas()
{
	QFile file("D:/QT/Programs/PSP Tool/Resource/Datas.json");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	file.write(QJsonDocument(TD.writeJson()).toJson());
	file.close();
}

void TotalData::getResults(E2Datas& datas) {

	//4 Part
	datas.E2Results[1] = datas.TotalTimes / datas.TotalUnits;
	datas.E2Results[2] = (datas.TotalTimes + TotalTimes) / (datas.TotalUnits + TotalUnits);
	datas.E2Results[4] = 60.0 / datas.E2Results[1];
	datas.E2Results[5] = 60.0 / datas.E2Results[2];
	datas.E2Results[7] = (double)datas.DefectData.size() / datas.TotalUnits * 1000;
	datas.E2Results[8] = (double)(DefectData[0] + DefectData[1] + datas.DefectData.size()) / (TotalUnits + datas.TotalUnits) * 1000;
	int defectDatas[6] = { 0 };
	for (int i = 0; i < datas.DefectData.size(); i++) {
		defectDatas[datas.DefectData[i].Inject]++;
		defectDatas[datas.DefectData[i].Remove]++;
	}
	if (defectDatas[0] + defectDatas[1])
	{
		datas.E2Results[10] = (double)defectDatas[2] / (defectDatas[0] + defectDatas[1]) * 100;
	}
	else {
		datas.E2Results[10] = 0;
	}
	if (DefectData[0] + DefectData[1] + defectDatas[0] + defectDatas[1])
	{
		datas.E2Results[11] = (double)(DefectData[2] + defectDatas[2]) / (DefectData[0] + DefectData[1] + defectDatas[0] + defectDatas[1]) * 100;
	}
	else {
		datas.E2Results[11] = 0;
	}

	datas.E2Results[13] = datas.PhaseTime[3] / (datas.PhaseTime[4] + datas.PhaseTime[5]);
	datas.E2Results[14] = (PhaseTime[3] + datas.PhaseTime[3]) / (PhaseTime[4] + PhaseTime[5] + datas.PhaseTime[4] + datas.PhaseTime[5]);
	datas.E2Results[16] = datas.TotalUnits;
	datas.E2Results[17] = TotalUnits + datas.TotalUnits;
	datas.E2Results[21] = datas.PhaseTime[0];
	datas.E2Results[25] = datas.PhaseTime[1];
	datas.E2Results[29] = datas.PhaseTime[2];
	datas.E2Results[33] = datas.PhaseTime[3];
	datas.E2Results[37] = datas.PhaseTime[4];
	datas.E2Results[41] = datas.PhaseTime[5];
	datas.E2Results[45] = datas.PhaseTime[6];
	datas.E2Results[49] = datas.TotalTimes;
	datas.E2Results[22] = datas.PhaseTime[0] + PhaseTime[0];
	datas.E2Results[26] = datas.PhaseTime[1] + PhaseTime[1];
	datas.E2Results[30] = datas.PhaseTime[2] + PhaseTime[2];
	datas.E2Results[34] = datas.PhaseTime[3] + PhaseTime[3];
	datas.E2Results[38] = datas.PhaseTime[4] + PhaseTime[4];
	datas.E2Results[42] = datas.PhaseTime[5] + PhaseTime[5];
	datas.E2Results[46] = datas.PhaseTime[6] + PhaseTime[6];
	datas.E2Results[50] = TotalTimes + datas.TotalTimes;
	datas.E2Results[23] = datas.E2Results[22] / datas.E2Results[50] * 100;
	datas.E2Results[27] = datas.E2Results[26] / datas.E2Results[50] * 100;
	datas.E2Results[31] = datas.E2Results[30] / datas.E2Results[50] * 100;
	datas.E2Results[35] = datas.E2Results[34] / datas.E2Results[50] * 100;
	datas.E2Results[39] = datas.E2Results[38] / datas.E2Results[50] * 100;
	datas.E2Results[43] = datas.E2Results[42] / datas.E2Results[50] * 100;
	datas.E2Results[47] = datas.E2Results[46] / datas.E2Results[50] * 100;
	datas.E2Results[51] = 100;
	int Totaldefect = 0;
	for (int i = 0; i < 6; i++)
	{
		Totaldefect += DefectData[i] + defectDatas[i];
	}
	datas.E2Results[55] = defectDatas[0];
	datas.E2Results[56] = defectDatas[0] + DefectData[0];

	datas.E2Results[58] = datas.E2Results[56] / datas.E2Results[26] * 60;
	datas.E2Results[60] = defectDatas[1];
	datas.E2Results[61] = defectDatas[1] + DefectData[1];

	datas.E2Results[63] = datas.E2Results[61] / datas.E2Results[30] * 60;
	datas.E2Results[65] = defectDatas[0] + defectDatas[1];
	datas.E2Results[66] = Totaldefect;
	datas.E2Results[67] = 100;
	datas.E2Results[69] = defectDatas[2];
	datas.E2Results[74] = defectDatas[3];
	datas.E2Results[79] = defectDatas[4];
	datas.E2Results[84] = datas.E2Results[65];
	datas.E2Results[70] = DefectData[2] + defectDatas[2];
	datas.E2Results[75] = DefectData[3] + defectDatas[3];
	datas.E2Results[80] = DefectData[4] + defectDatas[4];
	datas.E2Results[85] = Totaldefect;
	if (Totaldefect)
	{
		datas.E2Results[57] = datas.E2Results[56] / Totaldefect * 100;
		datas.E2Results[62] = datas.E2Results[61] / Totaldefect * 100;
		datas.E2Results[71] = datas.E2Results[70] / datas.E2Results[85] * 100;
		datas.E2Results[76] = datas.E2Results[75] / datas.E2Results[85] * 100;
		datas.E2Results[81] = datas.E2Results[80] / datas.E2Results[85] * 100;
	}
	else {
		datas.E2Results[57] = 0;
		datas.E2Results[62] = 0;
		datas.E2Results[71] = 0;
		datas.E2Results[76] = 0;
		datas.E2Results[81] = 0;
	}
	datas.E2Results[86] = 100;
	datas.E2Results[72] = datas.E2Results[70] / datas.E2Results[34] * 60;
	datas.E2Results[77] = datas.E2Results[75] / datas.E2Results[38] * 60;
	datas.E2Results[82] = datas.E2Results[80] / datas.E2Results[42] * 60;
	if (TotalTimes == 0)
	{
		datas.E2Results[0] = -1;
		datas.E2Results[3] = -1;
		datas.E2Results[6] = -1;
		datas.E2Results[9] = -1;
		datas.E2Results[12] = -1;
		datas.E2Results[15] = -1;
		datas.E2Results[18] = -1;
		datas.E2Results[19] = -1;
		datas.E2Results[20] = -1;
		datas.E2Results[24] = -1;
		datas.E2Results[28] = -1;
		datas.E2Results[32] = -1;
		datas.E2Results[36] = -1;
		datas.E2Results[40] = -1;
		datas.E2Results[44] = -1;
		datas.E2Results[48] = -1;
		datas.E2Results[52] = -1;
		datas.E2Results[53] = -1;
		datas.E2Results[54] = -1;
		datas.E2Results[59] = -1;
		datas.E2Results[64] = -1;
		datas.E2Results[68] = -1;
		datas.E2Results[73] = -1;
		datas.E2Results[78] = -1;
		datas.E2Results[83] = -1;

	}
	else {
		datas.E2Results[0] = TotalTimes / TotalUnits;
		datas.E2Results[3] = 60.0 / datas.E2Results[0];
		datas.E2Results[6] = (double)(DefectData[0] + DefectData[1]) / TotalUnits * 1000;

		datas.E2Results[12] = PhaseTime[3] / (PhaseTime[4] + PhaseTime[5]);
		datas.E2Results[15] = (MaxUnit + MinUnit) / 2;
		datas.E2Results[16] = datas.TotalUnits;
		datas.E2Results[17] = TotalUnits + datas.TotalUnits;
		datas.E2Results[48] = datas.E2Results[0] * datas.E2Results[15];
		datas.E2Results[52] = (datas.E2Results[18] + datas.E2Results[15]) * datas.E2Results[48];
		datas.E2Results[53] = (datas.E2Results[19] + datas.E2Results[15]) * datas.E2Results[48];
		datas.E2Results[20] = datas.E2Results[48] * PhaseTime[0] / TotalTimes;
		datas.E2Results[24] = datas.E2Results[48] * PhaseTime[1] / TotalTimes;
		datas.E2Results[28] = datas.E2Results[48] * PhaseTime[2] / TotalTimes;
		datas.E2Results[32] = datas.E2Results[48] * PhaseTime[3] / TotalTimes;
		datas.E2Results[36] = datas.E2Results[48] * PhaseTime[4] / TotalTimes;
		datas.E2Results[40] = datas.E2Results[48] * PhaseTime[5] / TotalTimes;
		datas.E2Results[44] = datas.E2Results[48] * PhaseTime[6] / TotalTimes;
		if (DefectData[0] + DefectData[1])
		{
			datas.E2Results[9] = (double)DefectData[2] / (DefectData[0] + DefectData[1]) * 100;
			datas.E2Results[54] = datas.E2Results[64] * DefectData[0] / (DefectData[0] + DefectData[1]);
			datas.E2Results[59] = datas.E2Results[64] * DefectData[1] / (DefectData[0] + DefectData[1]);
		}
		else {
			datas.E2Results[9] = 0;
			datas.E2Results[54] = 0;
			datas.E2Results[59] = 0;
		}
		datas.E2Results[64] = datas.E2Results[6] * datas.E2Results[15] / 1000;
		if (DefectData[5])
		{
			datas.E2Results[68] = datas.E2Results[83] * DefectData[2] / DefectData[5];
			datas.E2Results[73] = datas.E2Results[83] * DefectData[3] / DefectData[5];
			datas.E2Results[78] = datas.E2Results[83] * DefectData[4] / DefectData[5];
		}
		else {
			datas.E2Results[68] = 0;
			datas.E2Results[73] = 0;
			datas.E2Results[78] = 0;
		}

		datas.E2Results[83] = datas.E2Results[64];

	}
	TotalTimes = datas.E2Results[50];
	TotalUnits = datas.E2Results[17];
	for (int i = 0; i < 7; i++)
	{
		PhaseTime[i] = datas.E2Results[22 + i * 4];
	}
	for (int i = 0; i < 3; i++)
	{
		DefectData[i] = datas.E2Results[56 + i * 5];
	}
	for (int i = 0; i < 4; i++)
	{
		DefectData[i] = datas.E2Results[70 + i * 5];
	}


	//2 Part
	if (TotalUnits != datas.TotalTimes)datas.E1Results[0] = datas.PlanUnits * TotalTimes / TotalUnits;
	else datas.E1Results[0] = -1;
	datas.E1Results[1] = datas.PlanUnits;
	datas.E1Results[2] = datas.TotalTimes;
	datas.E1Results[3] = datas.TotalUnits;
	datas.E1Results[4] = datas.TotalTimes / datas.TotalUnits;
	datas.E1Results[5] = TotalTimes;
	datas.E1Results[6] = TotalUnits;
	datas.E1Results[7] = TotalTimes / TotalUnits;
	MaxRate = max(MaxRate, datas.E1Results[4]);
	MinRate = min(MinRate, datas.E1Results[4]);
	datas.E1Results[8] = MaxRate;
	datas.E1Results[9] = MinRate;

}