/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef EDITORAREA_H
#define EDITORAREA_H

#include "polygon.h"
#include "track.h"
#include <QWidget>
#include <QGLWidget>
#include <QPainter>
#include <QList>
#include <QPainterPath>
#include <QMainWindow>

class EditorArea : public QGLWidget {
	Q_OBJECT
public:
	EditorArea(QWidget *parent = 0, QMainWindow *mainWindow = 0);
	void addPoly(PCB::Polygon *poly);
	void addTrack(Track *track);
	QList<QPolygonF> polys;
	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void setZoom(float z);
	void changeZoom(float dz);
	void updateView();
public slots:
protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
	float zoom;
	QMainWindow *mainWindow;
	QMatrix m;
	QPoint start, stop;
	bool started;
	QPoint pos;
	void drawGrid(QPainter *p);
	QSize minimumSize;
	
};
	


#endif