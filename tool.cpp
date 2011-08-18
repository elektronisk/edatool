#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include "tool.h"
#include <QDebug>
#include "edatool.h"
Tool::Tool(EDATool *mainWin) {
	this->mainWindow = mainWin;
	this->action = new QAction((QMainWindow*)mainWin);
}

Tool::~Tool() {
	delete this->action;
}

QMenu *Tool::getFileMenu() { return mainWindow->fileMenu;}
QMenu *Tool::getEditMenu() { return mainWindow->editMenu;}