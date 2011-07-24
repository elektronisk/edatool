/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <iostream>
#include <geos/indexStrtree.h>
#include "edatool.h"

EDATool::EDATool() {
	this->setWindowTitle(tr("EDATool"));

	QScrollArea *scrollArea = new QScrollArea;
	EditorArea *area = new EditorArea(scrollArea, this);
	scrollArea->setWidget(area);
	scrollArea->setWidgetResizable(true);
	QTabWidget *tabs = new QTabWidget(this);
	tabs->addTab(scrollArea, QString("Document"));
	this->setCentralWidget(tabs);
	
	this->menuBar()->addMenu(tr("File"));
	this->menuBar()->addMenu(tr("Edit"));
	
	
	this->statusBar()->showMessage("Welcome");
	
	Board board;
}