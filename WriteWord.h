#pragma once
#include <QString>
#include <QAxObject>
#include <qaxwidget.h>


class WriteWord
{
public:
	static void WriteWord1();
	static void WriteWord2();
	static void WriteWord3(int);
	static void WriteWord4(int);
	static void MergeAll();
private:
	static void MoveRight(QString, int i = 1);
	static void StartWord(QString);
	static void SaveClose(QString);
	static void ReadBookmark(QString = "");
	static QAxObject* word, * documents, * document, * allBookmarks;
	static int readBookmark;
};

