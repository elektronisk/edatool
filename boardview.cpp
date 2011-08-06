/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */
#include <QTime>
#include <QDebug>
#include <QCursor>
#include "boardview.h"
#include "track.h"
#include <iostream>
#include <QtCore/qmath.h>
BoardView::BoardView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent) {
	setTransform(QTransform().translate(0, this->height()).scale(1, -1));
	zoom = 1;
	zoomFactor = 0.8;
	this->setMouseTracking(true);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	started = false;
	setForegroundBrush(QBrush(Qt::white));
	setCursor(QCursor(Qt::BlankCursor));
	setDragMode(QGraphicsView::RubberBandDrag);
}

void BoardView::wheelEvent(QWheelEvent *event) {
	//QGraphicsView::wheelEvent(event);
	float dz = (event->delta() / 1200.0);
	
	if (dz < 0 && zoom*zoomFactor > 0.1) {
		zoom = zoom*zoomFactor;
		scale(zoomFactor, zoomFactor);	// zoom in
	} else if (dz > 0 && zoom*(1/0.8) < 20) {
		zoom = zoom*(1/zoomFactor);
		scale(1/zoomFactor, 1/zoomFactor);	// zoom out
	}
	std::cout << "Zoom: " << zoom << std::endl;
	this->invalidateScene();
	this->scene()->update();
}

void BoardView::mousePressEvent(QMouseEvent *event){
	QGraphicsView::mousePressEvent(event);
	if (event->button() == Qt::LeftButton) {
		if (!started) {
			start = mapToScene(event->pos());
			started = true;
		} else {
			stop = mapToScene(event->pos());
			Track *track = new Track(start.x(), start.y(), stop.x(), stop.y(), 10);
			this->scene()->addPolygon(track->shell, QPen(Qt::NoPen), QBrush(Qt::red));
			delete track;
			started = false;
		}
	} else if (event->button() == Qt::RightButton) {
		QList<QGraphicsItem*> list = items(event->pos());
		if (list.size() == 0)
			return;
		for (int i = 0; i < list.size(); i++) {
			this->scene()->removeItem(list.at(i));
		}
	} else if(event->button() == Qt::MiddleButton) {
		qDebug() << "There are" << items(event->pos()).size()
			<< "items at position" << mapToScene(event->pos());
	}
}

void BoardView::drawForeground (QPainter *painter, const QRectF & rect) {
	Q_UNUSED(rect);
	
	float x = sceneCursorPosition.x();
	float y = sceneCursorPosition.y();
	painter->setPen(QPen(Qt::white));
	float d = sceneCursorRect.boundingRect().height();
	
	painter->drawLine(QPointF(x-d, y), QPointF(x+d, y)); // horizontal line ----
	painter->drawLine(QPointF(x, y-d), QPointF(x, y+d)); // vert line |
}

void BoardView::mouseMoveEvent(QMouseEvent *event) {
	QGraphicsView::mouseMoveEvent(event);
	viewCursorPosition = event->pos();
	viewCursorRect = QRect(viewCursorPosition.x() - 20, viewCursorPosition.y() - 20, 40, 40);
	sceneCursorPosition = mapToScene(viewCursorPosition);
	sceneCursorRect = mapToScene(viewCursorRect);
	this->scene()->update();
}