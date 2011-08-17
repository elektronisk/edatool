/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#include "track.h"

Track::Track(QPointF p1, QPointF p2, qreal w) {
	setWidth(w);
	QGraphicsLineItem::QGraphicsLineItem(p1.x(), p1.y(), p2.x(), p2.y());
}

Track::Track(qreal x1, qreal y1, qreal x2, qreal y2, qreal w) {
	setWidth(w);
	QGraphicsLineItem::QGraphicsLineItem(x1, y1, x2, y2);
}
Track::~Track() {
	//delete polygon;
}