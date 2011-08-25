/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef BOARDVIEW_H
#define BOARDVIEW_H

class QWidget;
class QWheelEvent;
class QGraphicsScene;
class QMainWindow;
class QKeyEvent;
#include <QGraphicsView>
#include <QPointF>
#include "track.h"

class BoardView : public QGraphicsView {
public:
	BoardView(QMainWindow *main, QGraphicsScene *scene, QWidget *parent = 0);
	QPoint viewCursorPosition;
	QPointF sceneCursorPosition;
private:
	bool exitortho;
	Track *tempSegment1;
	Track *tempSegment2;
	QPointF wayPoint;
	QMainWindow *mainWindow;
	
	float zoomFactor;
	float zoom;
	bool routing;
	QPointF start, stop;
	void updateWayPoint();
protected:
	void drawForeground (QPainter *painter, const QRectF & rect);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
};

#endif