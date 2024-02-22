#pragma once
#include<vector>
#include<QString>
#include<qjsonarray.h>
#include<qjsondocument.h>
#include<qjsonobject.h>
#include<QJsonValue>


//If you want to set block empty, set value -1
class E1Datas {
public:
	int Date;//month*100 + date
	double StartTime;//h*60 + m
	double StopTime;
	double InterruptTime;
	int Units;
	int ID;
	bool Finished;
	QString PartName;
	QJsonObject writeJson();
	void readJson(QJsonValue);
};

class Defects {
public:
	int Date;
	int Type;
	int Inject;//0 D 1 C
	int Remove;//2 R 3 C 4 T
	double FixTime;
	int FixDefect;
	QString Description;
	QJsonObject writeJson();
	void readJson(QJsonValue);
};

class E2Datas {
public:
	int dataID;
	double TotalTimes;
	int TotalUnits;
	int PlanUnits;
	QString DataName;
	QString Language;
	int BeginDate;
	int Phase;
	double PhaseTime[7];//Planning, Design, Code, CodeReview, Compile, Test, Postmortem
	std::vector<Defects> DefectData;
	double E2Results[87];//Part1 0~19 Part2 20~53 Part3 54~86
	double E1Results[10];
	QJsonObject writeJson();
	void readJson(QJsonValue);
};

class TotalData {
public:
	//std::vector<std::vector<E1Datas>> Datas1;
	std::vector<E1Datas> Datas1;
	std::vector<E2Datas> Finished;
	std::vector<E2Datas> UnFinished;
	double TotalTimes;
	int TotalUnits;
	double PhaseTime[7];
	int DefectData[6];//Design, Code, CodeReview, Compile, Test, Total
	int MaxUnit, MinUnit;
	double MaxRate, MinRate;
	QString StudentName;
	QString InstrucorName;
	QString ClassName;
	void getResults(E2Datas& datas);
	QJsonObject writeJson();
	void readJson(QJsonValue);
	static void getDatas();
	static void saveDatas();
};

extern TotalData TD;

