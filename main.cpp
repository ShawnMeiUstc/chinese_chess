#include <QApplication>
#include <QtGlobal>
#include <QTime>
#include "Board.h"
#include "Choice.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	Choice ch;
	if (ch.exec() != QDialog::Accepted)
		return 0;

	MainWindow wnd(ch._selected);
	wnd.show();

	return app.exec();

}
