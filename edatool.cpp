/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <QGLWidget>
#include <iostream>
#include <geos/indexStrtree.h>
#include "edatool.h"

#include "routetool.h"

EDATool::EDATool() {
	this->setWindowTitle(tr("EDATool"));

	boardScene = new QGraphicsScene();
	
	boardView = new BoardView(this, boardScene);
	if (!QCoreApplication::arguments().contains("-nogl"))
		boardView->setViewport(new QGLWidget);
	
	QTabWidget *tabs = new QTabWidget(this);
	tabs->addTab(boardView, QString("Document"));
	tabs->setDocumentMode(true);
	this->setCentralWidget(tabs);
	
	this->fileMenu = this->menuBar()->addMenu(tr("File"));
	this->editMenu = this->menuBar()->addMenu(tr("Edit"));
	
	QLabel *t = new QLabel("LOL FU");
	t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->statusBar()->addPermanentWidget(t);
	t = new QLabel("MOAR TESTING");
	t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->statusBar()->addPermanentWidget(t);
	this->statusBar()->showMessage("showmessage", 2000);
	resize(700, 500);
	//Board board;
	toolBar = addToolBar("Tools");
	toolBar->setIconSize(QSize(16, 16));
	
	RouteTool *tool = new RouteTool(this);
	tool->install();
	
}
