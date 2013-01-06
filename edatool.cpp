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
	QTreeWidget *tree = new QTreeWidget(this);
	temp->setWindowTitle("Tool settings");
	temp->setWidget(tree);
	tree->setColumnCount(1);
	tree->setHeaderLabel("Name");
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
	cache = new QHash<QString, QGraphicsItemGroup*>();
	QFile file("C:\\Users\\andreas\\workspace\\edatool\\test.brd");
	EagleFormat *eagleFormat = new EagleFormat();
	eagleFormat->read(&file,cache);
	QHashIterator<QString, QGraphicsItemGroup*> i(*cache);
	while (i.hasNext()) {
		i.next();
		QTreeWidgetItem *item = new QTreeWidgetItem(tree, QStringList(i.key()));
	}
	connect(tree,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(itemClicked(QTreeWidgetItem*,QTreeWidgetItem*)));
}

void EDATool::itemClicked(QTreeWidgetItem* item,QTreeWidgetItem* previous) {
	boardScene->clear();
	boardScene->addItem(cache->value(item->text(0)));
}

void EDATool::layerToPenBrush(int layer, QPen &pen, QBrush &brush) {
	struct LayerDefinition {
		LayerDefinition(QString s, QColor c, Qt::BrushStyle bs){
			this->name = s;
			this->color = c;
			this->brushStyle = bs;
		}

		QString name;
		QColor color;
		enum Qt::BrushStyle brushStyle;
		int zorder;
	};
	LayerDefinition *ld[52];

	ld[0] = new LayerDefinition("Undefined", QColor(0,0,0,255), Qt::CrossPattern);
	ld[1] = new LayerDefinition("Top", QColor(255,0,0,127), Qt::SolidPattern);
	ld[16] = new LayerDefinition("Bottom", QColor(0,0,255,127), Qt::SolidPattern);
	ld[21] = new LayerDefinition("tPlace", QColor(255,255,255,127), Qt::SolidPattern);
	ld[29] = new LayerDefinition("tStop", QColor(0,255,0,127), Qt::BDiagPattern);
	ld[31] = new LayerDefinition("tCream", QColor(255,255,255,127), Qt::BDiagPattern);
	ld[51] = new LayerDefinition("tDocu", QColor(200,200,200,127), Qt::SolidPattern);
	if (!ld[layer]) {
		layer = 0; // default style
	}
	brush.setColor(ld[layer]->color);
	brush.setStyle(ld[layer]->brushStyle);
	brush.setTransform(QTransform::fromScale(0.005, 0.005));

	pen.setColor(ld[layer]->color);
	pen.setStyle(Qt::SolidLine);
}
