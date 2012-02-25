/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include <QPainter>
#include "wire.h"

Wire::Wire(QPointF _p1, QPointF _p2, qreal _w) {
	p1 = _p1;
	p2 = _p2;
	updateSnapPoints();
	width = _w;
}

Wire::Wire(qreal x1, qreal y1, qreal x2, qreal y2, qreal _w) {
	p1 = QPointF(x1,y1);
	p2 = QPointF(x2,y2);
	updateSnapPoints();
	width = _w;
}

void Wire::updateSnapPoints() {
	snapPoints.clear();
	snapPoints.append(p1);
	snapPoints.append(p2);
}

QRectF Wire::boundingRect() const {
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
void Wire::paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *widget){
	//p->drawRect(boundingRect());
	p->setPen(QPen(QBrush(QColor::fromRgba(qRgba(255, 0, 0, 128))), width, Qt::SolidLine, Qt::RoundCap));
	p->drawLine(p1, p2);

}

void Wire::setLine(const QLineF & line) {
	prepareGeometryChange();
	p1 = line.p1();
	p2 = line.p2();
	updateSnapPoints();
}

void Wire::setLine(qreal x1, qreal y1, qreal x2, qreal y2) {
	prepareGeometryChange();
	p1 = QPointF(x1,y1);
	p2 = QPointF(x2,y2);
	updateSnapPoints();
}
