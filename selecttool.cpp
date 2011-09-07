/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "selecttool.h"
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include "boardview.h"

SelectTool::SelectTool(EDATool *w) : Tool(w) {}

void SelectTool::install() {
	qDebug() << "Installing SelectTool";
	action->setIcon(QIcon::fromTheme("find")); /* random icon for now */
	action->setText("Selection tool");
	action->setIconVisibleInMenu(true);
	action->setCheckable(true);
	
	getPlaceMenu()->addAction(action);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(trigger(bool)));
	getToolBar()->addAction(action);
	
	getToolActionGroup()->addAction(action);
}

void SelectTool::uninstall() {
	qDebug() << "Uninstalling SelectTool";
	getPlaceMenu()->removeAction(action);
	getToolBar()->removeAction(action);
	getToolActionGroup()->removeAction(action);
}

void SelectTool::activate() {
	active = true;
	getBoardView()->setDragMode(QGraphicsView::RubberBandDrag);
	qDebug() << "selecttool activated";
}

void SelectTool::deactivate() {
	active = false;
	getBoardView()->setDragMode(QGraphicsView::NoDrag);
	qDebug() << "selecttool deactivated";
}

bool SelectTool::eventFilter(QObject *obj, QEvent *rawEvent) {
	return false;
}

void SelectTool::trigger(bool enabling) {
	if (enabling && !active) {
		activate();
	} else if (!enabling && active) {
		deactivate();
	}
}