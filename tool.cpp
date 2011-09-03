/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include "tool.h"
#include <QDebug>
#include "edatool.h"
class BoardView;
Tool::Tool(EDATool *mainWin) {
	this->mainWindow = mainWin;
	this->action = new QAction((QMainWindow*)mainWin);
	this->active = false;
}

Tool::~Tool() {
	delete this->action;
}

bool Tool::isActive() { return active; }

QMenu *Tool::getPlaceMenu() { return mainWindow->placeMenu;}
QMenu *Tool::getFileMenu() { return mainWindow->fileMenu;}
QMenu *Tool::getEditMenu() { return mainWindow->editMenu;}
BoardView *Tool::getBoardView() { return mainWindow->boardView; }
QGraphicsScene *Tool::getBoardScene() { return mainWindow->boardScene; }
QToolBar *Tool::getToolBar() { return mainWindow->toolBar; }
QActionGroup *Tool::getToolActionGroup() { return mainWindow->toolActionGroup; }