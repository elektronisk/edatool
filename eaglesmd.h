#ifndef SMD_H
#define SMD_H

#include "pcbgraphicsitem.h"

class EagleSmd : public PCBGraphicsItem {
public:
	EagleSmd(qreal, qreal, qreal, qreal, int, int, QString, bool, bool, bool);
	QRectF boundingRect() const;
	void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
	enum { Type = UserType + 2 };
	int type() const {
		return Type;
	}
private:
	qreal x, y, dx, dy;
	int layer, roundness;
	QString rot;
	bool stop, thermals, cream;
};

#endif // SMD_H
