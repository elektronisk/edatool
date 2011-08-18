/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <QGLWidget>
#include <iostream>
#include <geos/indexStrtree.h>
#include "edatool.h"
#include "boardview.h"
#include "routetool.h"

EDATool::EDATool() {
	this->setWindowTitle(tr("EDATool"));

	QGraphicsScene *boardScene = new QGraphicsScene();
	
	BoardView *boardView = new BoardView(this, boardScene);
	if (!QCoreApplication::arguments().contains("-nogl"))
		boardView->setViewport(new QGLWidget);
	
	qsrand(1);
	QGraphicsItem *temp;
	
	/*
	for (int i = 0; i < 100; i++) {
		QLineF line(qrand() % 200, qrand() % 200, qrand() % 200, qrand() % 200);
		temp = boardScene->addLine(line, QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::RoundCap));
		temp->setFlag(QGraphicsItem::ItemIsSelectable);
	}
	*/
	
	QGraphicsTextItem *text = new QGraphicsTextItem("My Text\nMultiline");
	text->setTextInteractionFlags(Qt::TextEditable);
	text->setDefaultTextColor(Qt::white);
	text->scale(1, -1);
	text->setFont(QFont("ISOCPEUR"));
	QGraphicsItemGroup *item = new QGraphicsItemGroup();
	item->addToGroup(text);
	boardScene->addItem(item);
	item->setPos(50, 50);
	
	
	QTabWidget *tabs = new QTabWidget(this);
	tabs->addTab(boardView, QString("Document"));
	
	this->setCentralWidget(tabs);
	
	this->fileMenu = this->menuBar()->addMenu(tr("File"));
	this->editMenu = this->menuBar()->addMenu(tr("Edit"));
	
	//this->statusBar()->showMessage("Welcome");
	QLabel *t = new QLabel("LOL FU");
	t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->statusBar()->addPermanentWidget(t);
	t = new QLabel("MOAR TESTING");
	t->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	this->statusBar()->addPermanentWidget(t);
	this->statusBar()->showMessage("showmessage", 2000);
	resize(700, 500);
	Board board;
	
	RouteTool *tool = new RouteTool(this);
	tool->install();
}
