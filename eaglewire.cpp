/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QPainter>
#include <QColor>
#include "edatool.h"
#include "eaglewire.h"

EagleWire::EagleWire(QPointF _p1, QPointF _p2, qreal _w, int _layer) {
	p1 = _p1;
	p2 = _p2;
	updateSnapPoints();
	width = _w;
	layer = _layer;
}

EagleWire::EagleWire(qreal x1, qreal y1, qreal x2, qreal y2, qreal _w, int _layer) {
	p1 = QPointF(x1,y1);
	p2 = QPointF(x2,y2);
	updateSnapPoints();
	width = _w;
	layer = _layer;
}

void EagleWire::updateSnapPoints() {
	snapPoints.clear();
	snapPoints.append(p1);
	snapPoints.append(p2);
}

QRectF EagleWire::boundingRect() const {
	const qreal x1 = p1.x();
	const qreal x2 = p2.x();
	const qreal y1 = p1.y();
	const qreal y2 = p2.y();
	const qreal halfwidth = width/2;
	qreal lx = qMin(x1, x2)-halfwidth;
	qreal rx = qMax(x1, x2)+halfwidth;
	qreal ty = qMin(y1, y2)-halfwidth;
	qreal by = qMax(y1, y2)+halfwidth;
	return QRectF(lx, ty, rx - lx, by - ty);
}



void EagleWire::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *widget){
	//p->drawRect(boundingRect());
	QBrush brush; QPen pen;
	EDATool::layerToPenBrush(layer, pen, brush);
	p->setBrush(brush);
	pen.setCapStyle(Qt::RoundCap);
	pen.setWidthF(width);
	p->setPen(pen);
	p->drawLine(p1, p2);

}

void EagleWire::setLine(const QLineF & line) {
	prepareGeometryChange();
	p1 = line.p1();
	p2 = line.p2();
	updateSnapPoints();
}

void EagleWire::setLine(qreal x1, qreal y1, qreal x2, qreal y2) {
	prepareGeometryChange();
	p1 = QPointF(x1,y1);
	p2 = QPointF(x2,y2);
	updateSnapPoints();
}
