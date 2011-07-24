#include <QApplication>
#include "edatool.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	EDATool edatool;
	edatool.show();
	app.exec();
}