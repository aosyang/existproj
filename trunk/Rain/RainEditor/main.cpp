#include "raineditor.h"
#include <QtGui/QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//  π”√”Ô—‘∑≠“Î
	QTranslator translator;
	translator.load("raineditor_zh");
	a.installTranslator(&translator);

	RainEditor w;
	w.show();
	return a.exec();
}
