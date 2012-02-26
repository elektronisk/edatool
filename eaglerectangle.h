#ifndef RECT_H
#define RECT_H

#include "pcbgraphicsitem.h"

class EagleRectangle : public PCBGraphicsItem {
public:
	EagleRectangle(qreal _x1, qreal _y1, qreal _x2, qreal _y2, int _layer, QString _rot);
	QRectF boundingRect() const;
	void paint(QPainter *p, const QStyleOptionGraphicsItem *opt, QWidget *w);
	enum { Type = UserType + 4 };
	int type() const {
		return Type;
	}
private:
	qreal x1, y1, x2, y2;
	QString rot;
};

#endif // RECT_H
