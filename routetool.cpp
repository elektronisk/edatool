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
#include <QKeySequence>
#include "boardview.h"
#include "edatool.h"

RouteTool::RouteTool(EDATool *w) : Tool(w) {}

void RouteTool::install() {
	qDebug() << "Installing RouteTool";
	action->setIcon(QIcon::fromTheme("edit-copy")); /* random icon for now */
	action->setText("In&teractive route");
	action->setIconVisibleInMenu(true);
	action->setCheckable(true);
	//action->setShortcut(QKeySequence(tr("T")));
	getPlaceMenu()->addAction(action);
	connect(action, SIGNAL(toggled(bool)), this, SLOT(trigger(bool)));
	getToolBar()->addAction(action);
	getToolActionGroup()->addAction(action);
	
	routing = false;
	tempSegment1 = 0;
	tempSegment2 = 0;
	exitortho = false;
}

void RouteTool::uninstall() {
	if (active) {
		qDebug() << "Cannot uninstall active tool (RouteTool)";
		return;
	}
	qDebug() << "Uninstalling RouteTool";
	getPlaceMenu()->removeAction(action);
	getToolBar()->removeAction(action);
	getToolActionGroup()->removeAction(action);
}

void RouteTool::activate() {
	active = true;
	getBoardView()->installEventFilter(this);
	qDebug() << "routetool activated";
}

void RouteTool::deactivate() {
	active = false;
	action->setChecked(false);
	getBoardView()->removeEventFilter(this);
	qDebug() << "routetool deactivated";
}

bool RouteTool::eventFilter(QObject *obj, QEvent *rawEvent) {
	Q_UNUSED(obj);
	if (rawEvent->type() == QEvent::MouseMove) {
		if (routing && tempSegment1 && tempSegment2)
			updateWayPoint();
	} else if (rawEvent->type() == QEvent::MouseButtonPress) {
		QMouseEvent *event = static_cast<QMouseEvent *>(rawEvent);
		
		if (event->button() == Qt::LeftButton) {
			if (!routing)
				routing = true;
			
			start = getBoardView()->sceneCursorPosition;
			
			if (tempSegment1 && tempSegment2) {
				tempSegment1->setFlag(QGraphicsItem::ItemIsSelectable);
				tempSegment2->setFlag(QGraphicsItem::ItemIsSelectable);
				tempSegment1->setFlag(QGraphicsItem::ItemIsMovable);
				tempSegment2->setFlag(QGraphicsItem::ItemIsMovable);
			}
			
			tempSegment1 = new Track(start, getBoardView()->sceneCursorPosition, 5);
			tempSegment2 = new Track(start, getBoardView()->sceneCursorPosition, 5);
			
			getBoardScene()->addItem(tempSegment1);
			getBoardScene()->addItem(tempSegment2);
			
			exitortho = !exitortho;
			
		} else if (event->button() == Qt::RightButton) {
			if (routing) {
				getBoardScene()->removeItem(tempSegment1);
				getBoardScene()->removeItem(tempSegment2);
			}
			routing = false;
		}
	} else if (rawEvent->type() == QEvent::KeyPress) {
		QKeyEvent *event = static_cast<QKeyEvent *>(rawEvent);
		if (event->key() == Qt::Key_Space) {
			exitortho = !exitortho;
			updateWayPoint();
		}
	}
	return false; // do not eat the event
	
}

void RouteTool::updateWayPoint() {
	if (tempSegment1 && tempSegment2) {
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
		
		exitortho ? pRef = p1 : pRef = p2;
		
		int dxpositive_sign = (dx > 0) ? 1 : -1;	// 1 if dx is positive
		int dypositive_sign = (dy > 0) ? 1 : -1;	// 1 if dx is positive
		int exitortho_sign = (exitortho) ? 1 : -1;
		
		
		
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