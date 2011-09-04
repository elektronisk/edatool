/* 
 * Copyright (C) 2011 Andreas Bertheussen.
 * All rigts reserved, although later versions might be open-source licensed.
 */

#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsItem>
#include <QPen>
#include <QDebug>

class Track : public QGraphicsLineItem {
public:
	Track(QPointF p1, QPointF p2, qreal w);
	Track(qreal x1, qreal y1, qreal x2, qreal y2, qreal w);
	~Track();
	void setWidth(qreal w) {
		width = w;
		QPen pen(QBrush(QColor::fromRgba(qRgba(255, 0, 0, 128))), w, Qt::SolidLine, Qt::RoundCap);
		QGraphicsLineItem::setPen(pen);
	}
	enum { Type = UserType + 1 };
	int type() const {
		return Type;
	}
	QList<QPointF> snapPoints;
	void setLine(const QLineF & line);
	void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
protected:
	QVariant itemChange(GraphicsItemChange, QVariant &);
private:
	qreal width;
};


#endif