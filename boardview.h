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
#include "edatool.h"

class BoardView : public QGraphicsView {
public:
	BoardView(EDATool *main, QGraphicsScene *scene, QWidget *parent = 0);
	QPoint viewCursorPosition;
	QPointF sceneCursorPosition;

private:
	EDATool *mainWindow;
	QPointF wayPoint;
	bool controlKeyPressed;
	bool shiftKeyPressed;
	bool altKeyPressed;
	float zoomFactor;
	float zoom;
	bool snapped;
	QList<QPointF> snapPoints;
protected:
	void drawForeground (QPainter *painter, const QRectF & rect);
	void wheelEvent(QWheelEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
};

#endif
