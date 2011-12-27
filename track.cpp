/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "track.h"

Track::Track(QPointF p1, QPointF p2, qreal w) : QGraphicsLineItem(QLineF(p1, p2)) {
	snapPoints.append(p1);
	snapPoints.append(p2);
	setWidth(w);
	hasSnap = true;
}

Track::Track(qreal x1, qreal y1, qreal x2, qreal y2, qreal w) : QGraphicsLineItem(x1, y1, x2, y2) {
	snapPoints.append(QPointF(x1, y1));
	snapPoints.append(QPointF(x2, y2));
	setWidth(w);
	hasSnap = true;
}

QVariant Track::itemChange(GraphicsItemChange change, QVariant &value) {
	if (change == ItemPositionHasChanged) {
		snapPoints.clear();
		snapPoints.append(line().p1());
		snapPoints.append(line().p2());
		qDebug() << "position changed";
	}
	return QGraphicsLineItem::itemChange(change, value);
}

void Track::setLine(const QLineF &line) {
	snapPoints.clear();
	snapPoints.append(line.p1());
	snapPoints.append(line.p2());
	QGraphicsLineItem::setLine(line);
}
void Track::setLine(qreal x1, qreal y1, qreal x2, qreal y2) {
	this->setLine(QLineF(x1, y1, x2, y2));
}

Track::~Track() {
}
