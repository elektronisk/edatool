#ifndef SMD_H
#define SMD_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QDebug>

#include "pcbgraphicsitem.h"

class Smd : public PCBGraphicsItem
{
public:
	Smd(qreal, qreal, qreal, qreal);
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	enum { Type = UserType + 2 };
	int type() const {
		return Type;
	}
private:
	qreal x, y, dx, dy;
};

#endif // SMD_H
