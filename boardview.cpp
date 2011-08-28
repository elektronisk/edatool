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
#include <QMenu>
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
	if (true) {
		d = qMax(height(), width()) * 1/zoom;
	}
	// todo: consolidate several drawLine into drawLines
	painter->drawLine(QPointF(x-d, y), QPointF(x+d, y)); // horizontal line ----
	painter->drawLine(QPointF(x, y-d), QPointF(x, y+d)); // vert line |
	painter->drawRect(QRectF(x-w, y-w, 2*w, 2*w));
	
	painter->drawLine(QPointF(-10, 0), QPointF(10, 0));
	painter->drawLine(QPointF(0, -10), QPointF(0, 10));
	painter->drawLine(QPointF(10, 0), QPointF(8, -2));
	painter->drawLine(QPointF(10, 0), QPointF(8, 2));
	painter->drawLine(QPointF(0, 10), QPointF(-2, 8));
	painter->drawLine(QPointF(0, 10), QPointF(2, 8));
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
