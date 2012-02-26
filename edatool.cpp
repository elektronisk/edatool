/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <QGLWidget>
#include <iostream>
#include "edatool.h"
#include "eagleformat.h"
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

	QFile file("C:\\Users\\andreas\\workspace\\edatool\\test.brd");
	EagleFormat *eagleFormat = new EagleFormat();
	eagleFormat->read(&file, boardScene);

}

QColor EDATool::layerToColor(int layer) {
	typedef struct LayerDefinition_t {
		QString name;
		QRgb color;
		enum Qt::BrushStyle brushStyle;
	} LayerDefinition;
	LayerDefinition ld[52];
	ld[1].name = "Top";
	ld[1].color = qRgba(255,0,0,127);
	ld[1].brushStyle = Qt::SolidPattern;
	ld[16].name = "Bottom";
	ld[16].color = qRgba(0,0,255,127);
	ld[16].brushStyle = Qt::SolidPattern;
	ld[21].name = "tPlace";
	ld[21].color = qRgba(255,255,255,127);
	ld[21].brushStyle = Qt::SolidPattern;
	ld[29].name = "tStop";
	ld[29].color = qRgba(0,255,0,127);
	ld[29].brushStyle = Qt::SolidPattern;
	ld[31].name = "tCream";
	ld[31].color = qRgba(255,255,255,255);
	ld[31].brushStyle = Qt::BDiagPattern;
	ld[51].name = "tDocu";
	ld[51].color = qRgba(200,200,200,127);
	ld[51].brushStyle = Qt::SolidPattern;

	QColor c(ld[layer].color);
	return c;
}

Qt::BrushStyle EDATool::layerToBrushStyle(int layer) {
	typedef struct LayerDefinition_t {
		QString name;
		QRgb color;
		enum Qt::BrushStyle brushStyle;
	} LayerDefinition;
	LayerDefinition ld[52];
	ld[1].name = "Top";
	ld[1].color = qRgb(255,0,0);
	ld[1].brushStyle = Qt::SolidPattern;
	ld[16].name = "Bottom";
	ld[16].color = qRgb(0,0,255);
	ld[16].brushStyle = Qt::SolidPattern;
	ld[21].name = "tPlace";
	ld[21].color = qRgb(255,255,255);
	ld[21].brushStyle = Qt::SolidPattern;
	ld[29].name = "tStop";
	ld[29].color = qRgb(0,255,0);
	ld[29].brushStyle = Qt::BDiagPattern;
	ld[31].name = "tCream";
	ld[31].color = qRgb(255,255,255);
	ld[31].brushStyle = Qt::BDiagPattern;
	ld[51].name = "tDocu";
	ld[51].color = qRgb(200,200,200);
	ld[51].brushStyle = Qt::SolidPattern;

	return ld[layer].brushStyle;
}
