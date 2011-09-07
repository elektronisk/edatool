/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */
#include <QTime>
#include <QDebug>
#include <QCursor>
#include <QMainWindow>
#include <QStatusBar>
#include <QGraphicsItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QMenu>
#include <QPointF>
#include <QLineF>
#include "boardview.h"
#include "track.h"

BoardView::BoardView(EDATool *main, QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
	mainWindow = main;
	setTransform(QTransform().translate(0, this->height()).scale(1, -1));
	zoom = 1;
	zoomFactor = 0.8;
	this->setMouseTracking(true);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setForegroundBrush(QBrush(Qt::white));
	setBackgroundBrush(Qt::gray);
	setCursor(QCursor(Qt::BlankCursor));
	setSceneRect(-500, -500, 1000, 1000);
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

void BoardView::mouseMoveEvent(QMouseEvent *event) {
	QGraphicsView::mouseMoveEvent(event);
	viewCursorPosition = event->pos();
	sceneCursorPosition = mapToScene(viewCursorPosition);
	
	/*qreal x = sceneCursorPosition.x();
	qreal y = sceneCursorPosition.y();
	qreal s = 1.0;
	qreal sh = s/2.0;
	
	if (x < 0) {
		x = x-sh - fmod(x-sh,s);
	} else {
		x = x+sh - fmod(x+sh,s);
	}
	
	if (y < 0) {
		y = y-sh - fmod(y-sh,s);
	} else {
		y = y+sh - fmod(y+sh,s);
	}
	
	sceneCursorPosition = QPointF(x, y);
	*/
	this->snapPoints.clear();
	QList<QGraphicsItem *> nearby = items(viewCursorPosition.x()-10, viewCursorPosition.y()-10, 20, 20, Qt::IntersectsItemBoundingRect);
	for (int i = 0; i < nearby.size(); i++) {
		if (nearby.at(i)->type() > QGraphicsItem::UserType) {
			Track *track = qgraphicsitem_cast<Track*>(nearby.value(i));
			if (track) {
				this->snapPoints.append(track->snapPoints);
			}
		}
	}
	QPointF closest;
	if (snapPoints.size() > 0) {
		closest = snapPoints.at(0);
		for (int i = 1; i < snapPoints.size();  i++) {
			if (QLineF(snapPoints.at(i), sceneCursorPosition).length() < QLineF(closest, sceneCursorPosition).length()) {
				closest = snapPoints.at(i);
			}			
		}
		
		if (QLineF(closest, sceneCursorPosition).length() < 10) {
			sceneCursorPosition = closest;
		}
	}
	
	event->ignore(); // allow event to be handled by hooks installed by tools
	scene()->update();
}

void BoardView::drawForeground (QPainter *painter, const QRectF & rect) {
	Q_UNUSED(rect);
	
	float x = sceneCursorPosition.x();
	float y = sceneCursorPosition.y();
	painter->setPen(QPen(Qt::white));
	float w = 5 * 1/zoom;
	float d = 20 * 1/zoom;
	if (false) { // TODO: incorporate into settings
		d = qMax(height(), width()) * 1/zoom;
	}
	QVector<QPointF> cursorCross;
	cursorCross << QPointF(x-d, y) << QPointF(x+d, y) << QPointF(x, y-d) << QPointF(x, y+d);
	painter->drawLines(cursorCross);

	painter->drawRect(QRectF(x-w, y-w, 2*w, 2*w));		// centre square
	
	// paint origin
	QVector<QPointF> origin;
	origin << QPointF(-10, 0) << QPointF(10, 0) << QPointF(0, -10) << QPointF(0, 10);
	origin << QPointF(10, 0) << QPointF(8, -2) << QPointF(10, 0) << QPointF(8, 2);
	origin << QPointF(0, 10) << QPointF(-2, 8) << QPointF(0, 10) << QPointF(2, 8);
	painter->drawLines(origin);
	
	for (int i  = 0; i < snapPoints.size(); i++) {
		painter->drawPoint(snapPoints.at(i));
	}
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
	} else if (event->key() == Qt::Key_P) {
		mainWindow->placeMenu->popup(QCursor::pos());
	}
	QGraphicsView::keyPressEvent(event);
}
