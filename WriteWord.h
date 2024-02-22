#pragma once
#include <QString>
#include <QAxObject>
#include <qaxwidget.h>


class WriteWord
{
public:
	static void WriteWord1(std::vector<int> v);
	static void WriteWord2(std::vector<int> v);
	static void WriteWord3(int);
	static void WriteWord4(int);
	static void MergeAll(std::vector<int> v,int op[4]);
private:
	static void MoveRight(QString, int i = 1);
	static void StartWord(QString);
	static void SaveClose(QString);
	static void ReadBookmark(QString = "");
	static void AppendWord(int i0,int i1);
	static QAxObject* word, * documents, * document, * allBookmarks;
	static int readBookmark;
};

