/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */
#include <QTime>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QStatusBar>
#include <QGraphicsPolygonItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QtCore/qmath.h>
#include "boardview.h"
#include "track.h"
#include <iostream>
#include <QtCore/qmath.h>
BoardView::BoardView(QMainWindow *main, QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
	mainWindow = main;
	setTransform(QTransform().translate(0, this->height()).scale(1, -1));
	zoom = 1;
	zoomFactor = 0.8;
	temporaryItem = 0;
	tempSegment1 = 0;
	tempSegment2 = 0;
	this->setMouseTracking(true);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	started = false;
	setForegroundBrush(QBrush(Qt::white));
	setCursor(QCursor(Qt::BlankCursor));
	setDragMode(QGraphicsView::RubberBandDrag);
	exitortho = true;
}

void BoardView::wheelEvent(QWheelEvent *event) {
	
	float dz = (event->delta() / 1200.0);
	
	if (dz < 0 && zoom*zoomFactor > 0.1) {
		zoom = zoom*zoomFactor;
		scale(zoomFactor, zoomFactor);	// zoom in
	} else if (dz > 0 && zoom*(1/0.8) < 20) {
		zoom = zoom*(1/zoomFactor);
		scale(1/zoomFactor, 1/zoomFactor);	// zoom out
	}
	
	mainWindow->statusBar()->showMessage(QString("%1%").arg(qRound(zoom*100)));
}

void BoardView::mousePressEvent(QMouseEvent *event){
	if (event->button() == Qt::LeftButton) {
		if (!started) {
			start = mapToScene(event->pos());
			QLineF line(start, sceneCursorPosition);
			//temporaryItem = scene()->addLine(line, QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::RoundCap));
			tempSegment1 = scene()->addLine(line, QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::RoundCap));
			tempSegment2 = scene()->addLine(line, QPen(QBrush(Qt::red), 2, Qt::SolidLine, Qt::RoundCap));
			started = true;
		} else {
			stop = mapToScene(event->pos());
			started = false;
			if (stop == start) {
				qDebug() << "Zero-length track ignored";
				scene()->removeItem(temporaryItem);
			}
			//temporaryItem->setFlag(QGraphicsItem::ItemIsSelectable);
			tempSegment1->setFlag(QGraphicsItem::ItemIsSelectable);
			tempSegment2->setFlag(QGraphicsItem::ItemIsSelectable);
			
			return;	// skip selection
		}
	} else if (event->button() == Qt::RightButton) {
		if (started) {
			scene()->removeItem(tempSegment1);
			scene()->removeItem(tempSegment2);
		}
		started = false;
		return;
	} else if(event->button() == Qt::MiddleButton) {
		qDebug() << "There are" << items(event->pos()).size()
			<< "items at position" << mapToScene(event->pos());
	}
	
	QGraphicsView::mousePressEvent(event);
}

void BoardView::updateWayPoint() {
	if (tempSegment1 && tempSegment2 && started) {
		QPointF p1, p2, pRef;
		p1 = start;
		p2 = sceneCursorPosition;
		
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
		tempSegment2->setLine(QLineF(wayPoint, sceneCursorPosition));
	}
	
}

void BoardView::mouseMoveEvent(QMouseEvent *event) {
	QGraphicsView::mouseMoveEvent(event);
	viewCursorPosition = event->pos();
	sceneCursorPosition = mapToScene(viewCursorPosition);

	if (tempSegment1 && tempSegment2 && started) {
		QPointF p1, p2, pRef;
		p1 = start;
		p2 = sceneCursorPosition;
		
		float dx = p2.x() - p1.x();
		float dy = p2.y() - p1.y();
		if (dx == 0 || dy == 0 || dx == dy) {
			return; // special case, only need 1 segment
		}
		
		float b;	// b is base, only vertical or horizontal. a is 45 deg angled line.
		bool dxbiggest = false;
		
		float adx = qAbs(dx);
		float ady = qAbs(dy);
		
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
		tempSegment2->setLine(QLineF(wayPoint, sceneCursorPosition));
	}
	updateWayPoint();
	this->scene()->update();
}

void BoardView::drawForeground (QPainter *painter, const QRectF & rect) {
	Q_UNUSED(rect);
	
	float x = sceneCursorPosition.x();
	float y = sceneCursorPosition.y();
	painter->setPen(QPen(Qt::white));
	float d =  20 * 1/zoom;
	
	painter->drawLine(QPointF(x-d, y), QPointF(x+d, y)); // horizontal line ----
	painter->drawLine(QPointF(x, y-d), QPointF(x, y+d)); // vert line |
}

void BoardView::keyPressEvent(QKeyEvent *event) {
	QGraphicsScene *sc = scene();
	if (event->key() == Qt::Key_Delete) {
		QList<QGraphicsItem*> selectedItems = sc->selectedItems();
		if (selectedItems.size() == 0)
			return;
		for (int i = 0; i < selectedItems.size(); i++) {
			sc->removeItem(selectedItems.at(i));
		}
	} else if (event->key() == Qt::Key_Space) {
		exitortho = !exitortho;
		updateWayPoint();
		scene()->update();
	}
	QGraphicsView::keyPressEvent(event);
}