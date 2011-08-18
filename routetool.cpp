#include "routetool.h"
#include <QDebug>
#include <QIcon>
#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include "edatool.h"

RouteTool::RouteTool(EDATool *w) : Tool(w) {}

void RouteTool::install() {
	qDebug() << "Installing RouteTool";
	action->setIcon(QIcon::fromTheme("edit-undo")); /* random icon for now */
	action->setText("Interactive route");
	action->setIconVisibleInMenu(true);
	getFileMenu()->addAction(action);
	connect(action, SIGNAL(triggered()), this, SLOT(showmessage()));
}

void RouteTool::uninstall() {
	qDebug() << "Uninstalling RouteTool";
	getFileMenu()->removeAction(action);
}

void RouteTool::showmessage() {
	QMessageBox::warning(mainWindow, "LOL", "message", QMessageBox::Ok);
}