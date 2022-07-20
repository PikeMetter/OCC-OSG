
#include <QString>
#include <QApplication>

#include "occView.h"

int main(int argc, char** argv)
{

	QApplication a(argc,argv);
	OccView w;
	w.show();
	return a.exec();
}
