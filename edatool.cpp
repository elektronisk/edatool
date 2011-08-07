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
EDATool::EDATool() {
	this->setWindowTitle(tr("EDATool"));

	QGraphicsScene *boardScene = new QGraphicsScene();
	
	BoardView *boardView = new BoardView(this, boardScene);
	boardScene->setBackgroundBrush(Qt::black);
	boardView->setViewport(new QGLWidget);
	
	qsrand(1);
	QGraphicsItem *temp;
	for (int i = 0; i < 100; i++) {
		QLineF line(qrand() % 200, qrand() % 200, qrand() % 200, qrand() % 200);
		temp = boardScene->addLine(line, QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::RoundCap));
		temp->setFlag(QGraphicsItem::ItemIsSelectable);
	}
	
	QGraphicsTextItem *text = new QGraphicsTextItem("My Text\nMultiline");
	text->setTextInteractionFlags(Qt::TextEditable);
	text->setDefaultTextColor(Qt::white);
	text->scale(1, -1);
	text->setPos(10, 10);
	boardScene->addItem(text);
	
	QTabWidget *tabs = new QTabWidget(this);
	tabs->addTab(boardView, QString("Document"));
	
	this->setCentralWidget(tabs);
	
	this->menuBar()->addMenu(tr("File"));
	this->menuBar()->addMenu(tr("Edit"));
	
	
	this->statusBar()->showMessage("Welcome");
	
	Board board;
}