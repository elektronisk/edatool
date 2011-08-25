/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "routetool.h"
#include <QDebug>
#include <QIcon>
#include <QAction>
#include <QMainWindow>
#include <QMenuBar>
#include <QEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QToolBar>
#include "boardview.h"
#include "edatool.h"

RouteTool::RouteTool(EDATool *w) : Tool(w) {}

void RouteTool::install() {
	qDebug() << "Installing RouteTool";
	action->setIcon(QIcon::fromTheme("edit-copy")); /* random icon for now */
	action->setText("Interactive route");
	action->setIconVisibleInMenu(true);
	action->setCheckable(true);
	getFileMenu()->addAction(action);
	connect(action, SIGNAL(triggered(bool)), this, SLOT(trigger(bool)));
	getToolBar()->addAction(action);
}

void RouteTool::uninstall() {
	if (active) {
		qDebug() << "Cannot uninstall active tool (RouteTool)";
		return;
	}
	qDebug() << "Uninstalling RouteTool";
	getFileMenu()->removeAction(action);
	getToolBar()->removeAction(action);
}

void RouteTool::activate() {
	active = true;
	getBoardView()->installEventFilter(this);
}

void RouteTool::deactivate() {
	active = false;
	getBoardView()->removeEventFilter(this);
}

bool RouteTool::eventFilter(QObject *obj, QEvent *event) {
	if (event->type() == QEvent::MouseMove) {
		QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
		qDebug() << "In mouse event filter for qgraphicsview: " << mouseEvent->pos();
	}
	return false; // do not eat the event
}

void RouteTool::updateWayPoint() {
	qDebug() << "in waypoint update";
	if (tempSegment1 && tempSegment2 && active) {
		QPointF p1, p2, pRef;
		p1 = start;
		p2 = getBoardView()->sceneCursorPosition;
		
		float b;	// b is base, only vertical or horizontal. a is 45 deg angled line.
		bool dxbiggest = false;
		
		float dx = p2.x() - p1.x();
		float dy = p2.y() - p1.y();
		float adx = qAbs(dx);
		float ady = qAbs(dy);
		
		if (adx == 0 || ady == 0 || adx == ady) {
			return; // special case, only need 1 segment
		}
		
		if (adx > ady) {
			b = adx - ady;
			dxbiggest = true;
		} else {
			b = ady - adx;
		}
		
		pRef = p1;
		int dxpositive_sign = (dx > 0) ? 1 : -1;	// 1 if dx is positive
		int dypositive_sign = (dy > 0) ? 1 : -1;	// 1 if dx is positive
		int exitortho_sign = (exitortho) ? 1 : -1;
		
		if (!exitortho)
			pRef = p2;
		
		if (dxbiggest) {
			wayPoint = QPointF(pRef.x() + dxpositive_sign*exitortho_sign*b, pRef.y());
		} else {
			wayPoint = QPointF(pRef.x(), pRef.y() + dypositive_sign*exitortho_sign*b);
		}
		
		tempSegment1->setLine(QLineF(start, wayPoint));
		tempSegment2->setLine(QLineF(wayPoint, getBoardView()->sceneCursorPosition));
	}
}

void RouteTool::trigger(bool enabling) {
	enabling ? activate() : deactivate();
}