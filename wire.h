/*
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsItem>
#include <QPen>
#include <QDebug>

#include "pcbgraphicsitem.h"

class Wire : public PCBGraphicsItem {
public:
	Wire(QPointF p1, QPointF p2, qreal w);
	Wire(qreal x1, qreal y1, qreal x2, qreal y2, qreal w);
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);

	enum { Type = UserType + 1 };
	int type() const {
		return Type;
	}
	void setLine(const QLineF & line);
	void setLine(qreal x1, qreal y1, qreal x2, qreal y2);

private:
	void updateSnapPoints();
	QPointF p1, p2;
	qreal width;
};


#endif
