/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

class QWidget;
#include <QWheelEvent>
class QGraphicsScene;
#include <QGraphicsView>
#include <QPointF>

class BoardView : public QGraphicsView {
public:
	BoardView(QGraphicsScene *scene, QWidget *parent = 0);
private:
	QPoint viewCursorPosition;
	QPointF sceneCursorPosition;
	QRect viewCursorRect;
	QPolygonF sceneCursorRect;
	float zoomFactor;
	float zoom;
	bool started;
	QPointF start, stop;
protected:
	void drawForeground (QPainter *painter, const QRectF & rect);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
};

#endif