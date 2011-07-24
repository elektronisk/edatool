/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QtGui>
#include <iostream>
#include "editorarea.h"

EditorArea::EditorArea(QWidget *parent, QMainWindow *mainWindow) : QGLWidget(parent) {
	this->zoom = 1;
	this->minimumSize = QSize(500, 500);
	this->mainWindow = mainWindow;
	started = false;
	m.translate(0, height());
	m.scale(zoom, -zoom);
	this->setMouseTracking(true);
}

void EditorArea::setZoom(float z) { //absolute zoom. z = 1 means 1mm = 1pixel
	if (z >= 0.1)
		this->zoom = z;
}
void EditorArea::changeZoom(float dz) {
	
	if (dz == 0)
		return;
	if (dz < 0 && zoom*0.9 > 0.1) {
		zoom = zoom* 0.9;
	} else if (dz > 0 && zoom*(1/0.9) > 0.1) {
		zoom = zoom* (1/0.9);
	}
	std::cout << "Zoom changed to: " << zoom << std::endl;
}

void EditorArea::addPoly(PCB::Polygon *poly) {
	this->polys.append(poly->shell);
}

void EditorArea::addTrack(Track *track) {
	this->polys.append(track->shell);
}

QSize EditorArea::minimumSizeHint() const {
	return minimumSize*zoom;
}
QSize EditorArea::sizeHint() const {
	return minimumSize*zoom;
}
void EditorArea::paintEvent(QPaintEvent *e) {
	// std::cout << "got paint event at " << e->rect().x() << "," << e->rect().y() << " " << e->rect().width() << "-" << e->rect().height() << std::endl;
	QPainter p(this);
	//m.reset();
	//m.translate(0, height());
	//m.scale(zoom, -zoom);
	p.setRenderHint(QPainter::HighQualityAntialiasing);
	p.setWorldTransform(QTransform(m));
	drawGrid(&p);
	p.setBrush(QColor::fromRgb(255,0,0));
	p.setPen(QPen(QColor::fromRgb(0,0,0,0)));
	for (int i = 0; i  < polys.size(); i++) {
		p.drawPolygon(polys[i]);
	}
	p.setPen(QPen(QColor::fromRgb(0,0,255)));
	QPolygonF poly;
	for (int i = 0; i < polys.size(); i++) {
		if (polys[i].containsPoint(pos,Qt::OddEvenFill)) {
			poly = poly.united(polys[i]);
		}
	}
	p.drawPolygon(poly);
	//p.drawRect(0,0, pos.x(), pos.y());
}
void EditorArea::drawGrid(QPainter *p) {
	for (int i = 0; i < 1000; i+= 10) {
		for (int j = 0; j < 1000; j+= 10) {
			p->drawPoint(i,j);
		}
	}
}
void EditorArea::mousePressEvent(QMouseEvent *event) {
	QMenu menu;
	
	if (event->button() == Qt::LeftButton) {
		if (!started) {
			start = event->pos()*m.inverted();
			started = true;
		} else {
			stop = event->pos()*m.inverted();
			std::cout << start.x() << " " << start.y() <<" " << stop.x() <<" " << stop.y() << std::endl;
			Track *track = new Track(start.x(), start.y(), stop.x(), stop.y(), 15);
			addTrack(track);
			delete track;
			started = false;
		}
	} else if (event->button() == Qt::RightButton) {
		for (int i = 0; i < polys.size(); i++) {
			if (polys[i].containsPoint(event->pos()*m.inverted(),Qt::OddEvenFill)) {
				menu.addAction(QString("Poly %1").arg(i));
				
				//i--;
			}
		}

		menu.exec(QCursor::pos());
	}
	update();
}
void EditorArea::mouseMoveEvent(QMouseEvent *event) {
	pos = event->pos()*m.inverted();
	mainWindow->statusBar()->showMessage(QString("Pos: x: %1 y: %2").arg(pos.x()).arg(pos.y()));

	this->update();
}

void EditorArea::wheelEvent(QWheelEvent *event) {
	changeZoom(event->delta() / 1200.0);
	updateGeometry();
	update();
}

void EditorArea::resizeEvent(QResizeEvent *event) {
	m.reset();
	m.translate(0, height());
	m.scale(zoom, -zoom);
	QWidget::resizeEvent(event);
}

void EditorArea::updateView() {
	m.reset();
	m.translate(0, height());
	m.scale(zoom, -zoom);
	updateGeometry();
}