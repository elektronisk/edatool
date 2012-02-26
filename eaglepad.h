#ifndef PAD_H
#define PAD_H

#include "pcbgraphicsitem.h"

class QDomElement;

class EaglePad : public PCBGraphicsItem {
public:
	enum PadShape { Square, Round, Octagon, Long, Offset };
	EaglePad(qreal _x, qreal _y, qreal _drill, qreal _diameter, PadShape _shape, bool stop, bool thermals, bool first);
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	enum { Type = UserType + 3 };
	int type() const {
		return Type;
	}
	static PadShape stringToPadShape(QString shape);
private:
	qreal x, y, drill, diameter;
	PadShape shape;
	QPolygonF octagon;
	void generateOctagon();
};

#endif // PAD_H
