/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <QGLWidget>
#include <iostream>
#include "edatool.h"

#include "routetool.h"
#include "selecttool.h"

EDATool::EDATool() {
	this->setWindowTitle(tr("EDATool"));

	boardScene = new QGraphicsScene();
	
	boardView = new BoardView(this, boardScene);
	if (!QCoreApplication::arguments().contains("-nogl"))
		boardView->setViewport(new QGLWidget);
	
	QTabWidget *tabs = new QTabWidget(this);
	tabs->setFocusPolicy(Qt::NoFocus); // don't let the tab header itself steal focus
	tabs->addTab(boardView, QString("Document"));
	tabs->setDocumentMode(true);
	this->setCentralWidget(tabs);
	QDockWidget *temp = new QDockWidget(this);
	QPushButton *button = new QPushButton(temp);

	temp->setWindowTitle("Tool settings");
	temp->setWidget(button);

	button->setText("Lols");
	this->addDockWidget(Qt::LeftDockWidgetArea, temp);
	
	this->fileMenu = this->menuBar()->addMenu(tr("File"));
	this->editMenu = this->menuBar()->addMenu(tr("Edit"));
	this->placeMenu = this->menuBar()->addMenu(tr("&Place"));
	
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
	
	toolActionGroup = new QActionGroup(this);
	
	SelectTool *selTool = new SelectTool(this);
	selTool->install();
	RouteTool *tool = new RouteTool(this);
	tool->install();
}

