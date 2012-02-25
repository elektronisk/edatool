/*
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */
#include <iostream>
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
#include "wire.h"
#include "smd.h"

BoardView::BoardView(EDATool *main, QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
	mainWindow = main;
	setTransform(QTransform().translate(0, this->height()).scale(1, -1));
	zoom = 100;
	scale(zoom, zoom);
	zoomFactor = 0.8;
	this->setMouseTracking(true);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setForegroundBrush(QBrush(Qt::white));
	setBackgroundBrush(Qt::gray);
	setCursor(QCursor(Qt::BlankCursor));
	setSceneRect(-50, -50, 100, 100);

	//fitInView(-10, -10, 20, 20, Qt::KeepAspectRatioByExpanding);
	this->scene()->addRect(-10, -10, 20, 20);
	snapped = false;
}

void BoardView::wheelEvent(QWheelEvent *event) {
	
	float dz = (event->delta() / 1200.0);
	
	if (dz < 0 && zoom > 1) {
		zoom = zoom*zoomFactor;
		scale(zoomFactor, zoomFactor);	// zoom out
	} else if (dz > 0 && zoom < 50000) {
		zoom = zoom*(1/zoomFactor);
		scale(1/zoomFactor, 1/zoomFactor);	// zoom in
	}
	
	mainWindow->statusBar()->showMessage(QString("%1% x:%2 y:%3").arg(qRound(zoom)).arg(sceneCursorPosition.x()).arg(sceneCursorPosition.y()));
}

void BoardView::mouseMoveEvent(QMouseEvent *event) {
	QGraphicsView::mouseMoveEvent(event);
	viewCursorPosition = event->pos();
	sceneCursorPosition = mapToScene(viewCursorPosition); // may be modified later in this func because of snap
	if (!controlKeyPressed) {
		this->snapPoints.clear();
		this->snapPoints.append(QPointF(0,0));
		QList<QGraphicsItem *> nearby = items(viewCursorPosition.x()-10, viewCursorPosition.y()-10, 20, 20, Qt::IntersectsItemBoundingRect);
		for (int i = 0; i < nearby.size(); i++) {
			if (nearby.at(i)->type() >= QGraphicsItem::UserType +1) {
				PCBGraphicsItem *item = qgraphicsitem_cast<PCBGraphicsItem*>(nearby.value(i)); // TODO: check for specific graphicsitem type before casting
				if (!item->snapIgnore)
					this->snapPoints.append(item->snapPoints);
			}
		}
		QPointF closest;
		snapped = false;
		if (snapPoints.size() > 0) {
			closest = snapPoints.at(0);
			for (int i = 1; i < snapPoints.size();  i++) {
				if (QLineF(snapPoints.at(i), sceneCursorPosition).length() < QLineF(closest, sceneCursorPosition).length()) {
					closest = snapPoints.at(i);
				}
			}

			if (QLineF(closest, sceneCursorPosition).length() < 0.1) {
				sceneCursorPosition = closest;
				snapped = true;
			}
		}
	} else {
		snapped = false;
	}
	mainWindow->statusBar()->showMessage(QString("%1% x:%2 y:%3").arg(qRound(zoom)).arg(sceneCursorPosition.x()).arg(sceneCursorPosition.y()));
	event->ignore(); // allow event to be handled by hooks installed by tools
	scene()->update();
}

void BoardView::drawForeground (QPainter *painter, const QRectF & rect) {
	Q_UNUSED(rect);
	
	float x = sceneCursorPosition.x();
	float y = sceneCursorPosition.y();
	painter->setPen(QPen(Qt::white));
	float w = 5 /(zoom);
	float d = 20 /(zoom);
	if (false) { // TODO: incorporate into settings
		d = qMax(height(), width()) * 1/zoom;
	}
	QVector<QPointF> cursorCross;
	cursorCross << QPointF(x-d, y) << QPointF(x+d, y) << QPointF(x, y-d) << QPointF(x, y+d);
	painter->drawLines(cursorCross);
	if (snapped)
		painter->drawEllipse(sceneCursorPosition, w,w);
	//painter->drawRect(QRectF(x-w, y-w, 2*w, 2*w));		// centre square
	
	// paint origin
	QVector<QPointF> origin;
	origin << QPointF(-1, 0) << QPointF(1, 0) << QPointF(0, -1) << QPointF(0, 1);
	origin << QPointF(1, 0) << QPointF(0.8, -0.2) << QPointF(1, 0) << QPointF(0.8, 0.2);
	origin << QPointF(0, 1) << QPointF(-0.2, 0.8) << QPointF(0, 1) << QPointF(0.2, 0.8);
	painter->drawLines(origin);
	
	for (int i  = 0; i < snapPoints.size(); i++) {
		painter->setPen(QPen(Qt::blue));
		painter->drawPoint(snapPoints.at(i));
	}
}

void BoardView::keyReleaseEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Control) {
		controlKeyPressed = false;
	}
}

void BoardView::keyPressEvent(QKeyEvent *event) {
	QGraphicsScene *sc = scene();
	if (event->key() == Qt::Key_Control) {
		controlKeyPressed = true;
	} else if (event->key() == Qt::Key_Delete) {
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
